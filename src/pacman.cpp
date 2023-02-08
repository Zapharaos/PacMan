#include <SDL.h>

#include <iostream>
#include "../include/constants.h"
#include "../include/game.h"

SDL_Window* pWindow = nullptr;
SDL_Surface* win_surf = nullptr;
SDL_Surface* plancheSprites = nullptr;

SDL_Rect src_bg = { constants::BMP_MAP_START_X,constants::BMP_MAP_START_Y, constants::BMP_MAP_WIDTH,constants::BMP_MAP_HEIGHT }; // x,y, w,h (0,0) en haut a gauche
SDL_Rect bg = { constants::WINDOW_MAP_START_X,constants::WINDOW_MAP_START_Y, constants::WINDOW_MAP_WIDTH,constants::WINDOW_MAP_HEIGHT }; // ici scale x4

SDL_Rect ghost_blinky_r = { constants::BMP_GHOST_BLINKY_START_X + constants::BMP_ENTITY_OFFSET_TO_RIGHT_IMG,constants::BMP_GHOST_BLINKY_START_Y, constants::BMP_ENTITY_WIDTH,constants::BMP_ENTITY_HEIGHT };
SDL_Rect ghost_blinky_l = { constants::BMP_GHOST_BLINKY_START_X + constants::BMP_ENTITY_OFFSET_TO_LEFT_IMG,constants::BMP_GHOST_BLINKY_START_Y, constants::BMP_ENTITY_WIDTH,constants::BMP_ENTITY_HEIGHT };
SDL_Rect ghost_blinky_u = { constants::BMP_GHOST_BLINKY_START_X + constants::BMP_ENTITY_OFFSET_TO_UP_IMG,constants::BMP_GHOST_BLINKY_START_Y, constants::BMP_ENTITY_WIDTH,constants::BMP_ENTITY_HEIGHT };
SDL_Rect ghost_blinky_d = { constants::BMP_GHOST_BLINKY_START_X + constants::BMP_ENTITY_OFFSET_TO_DOWN_IMG,constants::BMP_GHOST_BLINKY_START_Y, constants::BMP_ENTITY_WIDTH,constants::BMP_ENTITY_HEIGHT };
SDL_Rect ghost_blinky = { 34,34, constants::WINDOW_CELL_WIDTH,constants::WINDOW_CELL_HEIGHT };     // ici scale x2

int count;
Game* game = nullptr;

void init()
{
	pWindow = SDL_CreateWindow("PacMan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, constants::WINDOW_MAP_WIDTH,constants::WINDOW_MAP_HEIGHT, SDL_WINDOW_SHOWN);
	win_surf = SDL_GetWindowSurface(pWindow);

	plancheSprites = SDL_LoadBMP("./pacman_sprites.bmp");
    count = 0;

    game = new Game(constants::MAP_WIDTH, constants::MAP_HEIGHT);
}


// fonction qui met à jour la surface de la fenetre "win_surf"
void draw()
{
    SDL_SetColorKey(plancheSprites, false, 0);
    SDL_BlitScaled(plancheSprites, &src_bg, win_surf, &bg);

    // petit truc pour faire tourner le fantome
    SDL_Rect* ghost_in = nullptr;
    switch (count/128)
    {
        case 0:
            ghost_in = &(ghost_blinky_r);
            ghost_blinky.x++;
            break;
        case 1:
            ghost_in = &(ghost_blinky_d);
            ghost_blinky.y++;
            break;
        case 2:
            ghost_in = &(ghost_blinky_l);
            ghost_blinky.x--;
            break;
        case 3:
            ghost_in = &(ghost_blinky_u);
            ghost_blinky.y--;
            break;
    }
    count =(count+1)%(512);

    // ici on change entre les 2 sprites sources pour une jolie animation.
    SDL_Rect ghost_in2 = *ghost_in;
    if ((count/4)%2)
        ghost_in2.x += constants::BMP_ENTITY_TOTAL_WIDTH;
        
    // couleur transparente
    SDL_SetColorKey(plancheSprites, true, 0);
    // copie du sprite zoomé
	SDL_BlitScaled(plancheSprites, &ghost_in2, win_surf, &ghost_blinky);
}



int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
		std::cerr <<"Echec de l'initialisation de la SDL "<<SDL_GetError() << std::endl;
		return 1;
    }

	init();
    // BOUCLE PRINCIPALE
	bool quit = false;
	while (!quit)
	{
		SDL_Event event;
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

        // Gestion du clavier        
        int nbk;
        const Uint8* keys = SDL_GetKeyboardState(&nbk);
        if (keys[SDL_SCANCODE_ESCAPE])
            quit = true;
        if (keys[SDL_SCANCODE_LEFT])
            puts("LEFT");
        if (keys[SDL_SCANCODE_RIGHT])
            puts("RIGHT");
        if (keys[SDL_SCANCODE_UP])
            puts("UP");
        if (keys[SDL_SCANCODE_DOWN])
            puts("DOWN");

        // AFFICHAGE
		draw();
		SDL_UpdateWindowSurface(pWindow); 
        // LIMITE A 60 FPS
		SDL_Delay(16); // utiliser SDL_GetTicks64() pour plus de precisions
	}
    SDL_Quit(); // ON SORT
    return 0;
}
