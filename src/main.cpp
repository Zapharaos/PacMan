#include <SDL.h>

#include <iostream>
#include "../include/constants.h"
#include "../include/game.h"
#include "../include/saveGame.h"

SDL_Window* pWindow = nullptr;
SDL_Surface* win_surf = nullptr;
SDL_Surface* plancheSprites = nullptr;

SDL_Rect src_bg = { constants::BMP_MAP_START_X,constants::BMP_MAP_START_Y, constants::BMP_MAP_WIDTH,constants::BMP_MAP_HEIGHT }; // x,y, w,h (0,0) en haut a gauche
SDL_Rect bg = { constants::WINDOW_MAP_START_X,constants::WINDOW_MAP_START_Y, constants::WINDOW_MAP_WIDTH,constants::WINDOW_MAP_HEIGHT }; // ici scale x4

SDL_Rect ghost_blinky_r = { constants::BMP_GHOST_BLINKY_START_X + constants::BMP_ENTITY_GHOST_OFFSET_TO_RIGHT_IMG,constants::BMP_GHOST_BLINKY_START_Y, constants::BMP_ENTITY_GHOST_WIDTH,constants::BMP_ENTITY_GHOST_HEIGHT };
SDL_Rect ghost_blinky_l = { constants::BMP_GHOST_BLINKY_START_X + constants::BMP_ENTITY_GHOST_OFFSET_TO_LEFT_IMG,constants::BMP_GHOST_BLINKY_START_Y, constants::BMP_ENTITY_GHOST_WIDTH,constants::BMP_ENTITY_GHOST_HEIGHT };
SDL_Rect ghost_blinky_u = { constants::BMP_GHOST_BLINKY_START_X + constants::BMP_ENTITY_GHOST_OFFSET_TO_UP_IMG,constants::BMP_GHOST_BLINKY_START_Y, constants::BMP_ENTITY_GHOST_WIDTH,constants::BMP_ENTITY_GHOST_HEIGHT };
SDL_Rect ghost_blinky_d = { constants::BMP_GHOST_BLINKY_START_X + constants::BMP_ENTITY_GHOST_OFFSET_TO_DOWN_IMG,constants::BMP_GHOST_BLINKY_START_Y, constants::BMP_ENTITY_GHOST_WIDTH,constants::BMP_ENTITY_GHOST_HEIGHT };
SDL_Rect ghost_blinky = { 32,32, constants::WINDOW_CELL_WIDTH,constants::WINDOW_CELL_HEIGHT };     // ici scale x2

int count_;
Game* game = nullptr;

void init()
{
	pWindow = SDL_CreateWindow("PacMan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, constants::WINDOW_MAP_WIDTH + constants::SCORE_BOARD_WIDTH ,constants::WINDOW_MAP_HEIGHT, SDL_WINDOW_SHOWN);
	win_surf = SDL_GetWindowSurface(pWindow);

	plancheSprites = SDL_LoadBMP(constants::PATH_FILE_PACMAN_SPRITES);
    count_ = 0;

    game = new Game(constants::MAP_WIDTH, constants::MAP_HEIGHT, constants::WINDOW_CELL_HEIGHT, constants::PATH_FILE_PACMAN_MAP, constants::LIVES);
}


// fonction qui met à jour la surface de la fenetre "win_surf"
void draw()
{
    SDL_SetColorKey(plancheSprites, false, 0);
    SDL_BlitScaled(plancheSprites, &src_bg, win_surf, &bg);

    game->drawStaticEntities(plancheSprites, win_surf);

    // couleur transparente
    SDL_SetColorKey(plancheSprites, true, 0);

    Pacman pacman = game->getPacman();
    SDL_Rect image = pacman.getSprite().getImage();
    SDL_Rect image_position = pacman.getImagePosition();
    SDL_BlitScaled(plancheSprites, &image, win_surf, &image_position);

    // petit truc pour faire tourner le fantome
    SDL_Rect* ghost_in = nullptr;
    switch (count_ / 128)
    {
        case 0:
            ghost_in = &(ghost_blinky_r);
            ghost_blinky.x+=constants::GHOST_SPEED;
            break;
        case 1:
            ghost_in = &(ghost_blinky_d);
            ghost_blinky.y+=constants::GHOST_SPEED;
            break;
        case 2:
            ghost_in = &(ghost_blinky_l);
            ghost_blinky.x-=constants::GHOST_SPEED;
            break;
        case 3:
            ghost_in = &(ghost_blinky_u);
            ghost_blinky.y-=constants::GHOST_SPEED;
            break;
    }
    count_ = (count_ + 1) % (512);
    // ici on change entre les 2 sprites sources pour une jolie animation.
    SDL_Rect ghost_in2 = *ghost_in;
    if ((count_ / 4) % 2)
        ghost_in2.x += constants::BMP_ENTITY_GHOST_TOTAL_WIDTH;
    // copie du sprite zoomé
    SDL_BlitScaled(plancheSprites, &ghost_in2, win_surf, &ghost_blinky);
}



int main(int argc, char** argv)
{
    //Save game test
    saveGame::saveGameState(50,50) ;
    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
		std::cerr <<"Echec de l'initialisation de la SDL " << SDL_GetError() << std::endl;
		return 1;
    }

	init();
    // BOUCLE PRINCIPALE
	bool quit = false;
    SDL_Event event;
    // Gestion du clavier
    int nbk;
    const Uint8* keys = SDL_GetKeyboardState(&nbk);
    directions last = NONE;

	while (!quit)
	{
		while (!quit && SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			default: break;
			}
		}

        SDL_PumpEvents();

        if (keys[SDL_SCANCODE_ESCAPE])
            quit = true;

        if (keys[SDL_SCANCODE_LEFT])
            last = game->move(last, directions::LEFT);
        else if (keys[SDL_SCANCODE_RIGHT])
            last = game->move(last, directions::RIGHT);
        else if (keys[SDL_SCANCODE_UP])
            last = game->move(last, directions::UP);
        else if (keys[SDL_SCANCODE_DOWN])
            last = game->move(last, directions::DOWN);
        else
            game->move(last);

        // AFFICHAGE
		draw();
		SDL_UpdateWindowSurface(pWindow);
        // LIMITE A 60 FPS
		SDL_Delay(16); // utiliser SDL_GetTicks64() pour plus de precisions
	}
    SDL_Quit(); // ON SORT
    return 0;
}
