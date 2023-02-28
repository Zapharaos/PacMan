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

SDL_Rect pacman_default = { constants::BMP_PACMAN_START_X,constants::BMP_PACMAN_START_Y, constants::BMP_ENTITY_GHOST_WIDTH,constants::BMP_ENTITY_GHOST_HEIGHT };
SDL_Rect pacman = { 32*10,32*20, constants::WINDOW_CELL_WIDTH,constants::WINDOW_CELL_HEIGHT };     // ici scale x2

int count_;
Game* game = nullptr;

SDL_Rect* pacman_in = nullptr;

void init()
{
	pWindow = SDL_CreateWindow("PacMan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, constants::WINDOW_MAP_WIDTH + constants::SCORE_BOARD_WIDTH ,constants::WINDOW_MAP_HEIGHT, SDL_WINDOW_SHOWN);
	win_surf = SDL_GetWindowSurface(pWindow);

	plancheSprites = SDL_LoadBMP(constants::PATH_FILE_PACMAN_SPRITES);
    count_ = 0;

    pacman_in = &(pacman_default);

    game = new Game(constants::MAP_WIDTH, constants::MAP_HEIGHT, constants::WINDOW_CELL_HEIGHT, constants::PATH_FILE_PACMAN_MAP, constants::LIVES);
}


// fonction qui met à jour la surface de la fenetre "win_surf"
void draw()
{
    SDL_SetColorKey(plancheSprites, false, 0);
    SDL_BlitScaled(plancheSprites, &src_bg, win_surf, &bg);

    // petit truc pour faire tourner le fantome
    SDL_Rect* ghost_in = nullptr;
    switch (count_ / 128)
    {
        case 0:
            ghost_in = &(ghost_blinky_r);
            ghost_blinky.x+=constants::SPEED_GHOST;
            break;
        case 1:
            ghost_in = &(ghost_blinky_d);
            ghost_blinky.y+=constants::SPEED_GHOST;
            break;
        case 2:
            ghost_in = &(ghost_blinky_l);
            ghost_blinky.x-=constants::SPEED_GHOST;
            break;
        case 3:
            ghost_in = &(ghost_blinky_u);
            ghost_blinky.y-=constants::SPEED_GHOST;
            break;
    }
    count_ = (count_ + 1) % (512);

    // ici on change entre les 2 sprites sources pour une jolie animation.
    SDL_Rect pacman_in2 = *pacman_in;
    SDL_Rect ghost_in2 = *ghost_in;
    if ((count_ / 4) % 2)
        ghost_in2.x += constants::BMP_ENTITY_GHOST_TOTAL_WIDTH;
        
    // couleur transparente
    SDL_SetColorKey(plancheSprites, true, 0);
    // copie du sprite zoomé
	SDL_BlitScaled(plancheSprites, &ghost_in2, win_surf, &ghost_blinky);
    SDL_BlitScaled(plancheSprites, &pacman_in2, win_surf, &pacman);
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

        /*if (keys[SDL_SCANCODE_ESCAPE])
        {
            puts("QUIT");
            quit = true;
        }*/
        if (keys[SDL_SCANCODE_LEFT])
            game->movePacman(directions::LEFT, &pacman);
        if (keys[SDL_SCANCODE_RIGHT])
            game->movePacman(directions::RIGHT, &pacman);
        if (keys[SDL_SCANCODE_UP])
            game->movePacman(directions::UP, &pacman);
        if (keys[SDL_SCANCODE_DOWN])
            game->movePacman(directions::DOWN, &pacman);

        // AFFICHAGE
		draw();
		SDL_UpdateWindowSurface(pWindow);
        // LIMITE A 60 FPS
		SDL_Delay(16); // utiliser SDL_GetTicks64() pour plus de precisions
	}
    SDL_Quit(); // ON SORT
    return 0;
}
