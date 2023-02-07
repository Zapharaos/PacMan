#include <SDL.h>

#include <iostream>
#include "../include/constants.h"

SDL_Window* pWindow = nullptr;
SDL_Surface* win_surf = nullptr;
SDL_Surface* plancheSprites = nullptr;

SDL_Rect src_bg = { constants::MAP_START_X,constants::MAP_START_Y, constants::MAP_WIDTH,constants::MAP_HEIGHT }; // x,y, w,h (0,0) en haut a gauche
SDL_Rect bg = { constants::MAP_SCALE_RATIO,constants::MAP_SCALE_RATIO, constants::MAP_SCALE_RATIO * constants::MAP_WIDTH, constants::MAP_SCALE_RATIO  * constants::MAP_HEIGHT}; // ici scale x4

SDL_Rect ghost_r = { constants::GHOST_START_X,constants::GHOST_START_Y, constants::GHOST_WIDTH,constants::GHOST_HEIGHT };
SDL_Rect ghost_l = { constants::GHOST_START_X + (constants::GHOST_WIDTH + 1) * 2,constants::GHOST_START_Y, constants::GHOST_WIDTH,constants::GHOST_HEIGHT };
SDL_Rect ghost_d = { constants::GHOST_START_X + (constants::GHOST_WIDTH + 1) * 6,constants::GHOST_START_Y, constants::GHOST_WIDTH,constants::GHOST_HEIGHT };
SDL_Rect ghost_u = { constants::GHOST_START_X + (constants::GHOST_WIDTH + 1) * 4,constants::GHOST_START_Y, constants::GHOST_WIDTH,constants::GHOST_HEIGHT };
SDL_Rect ghost = { 34,34, 32,32 };     // ici scale x2

int count;

void init()
{
	pWindow = SDL_CreateWindow("PacMan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, constants::MAP_SCALE_RATIO * constants::MAP_WIDTH + 8, constants::MAP_SCALE_RATIO  * constants::MAP_HEIGHT + 8, SDL_WINDOW_SHOWN);
	win_surf = SDL_GetWindowSurface(pWindow);

	plancheSprites = SDL_LoadBMP("./pacman_sprites.bmp");
    count = 0;
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
            ghost_in = &(ghost_r);
            ghost.x++;
            break;
        case 1:
            ghost_in = &(ghost_d);
            ghost.y++;
            break;
        case 2:
            ghost_in = &(ghost_l);
            ghost.x--;
            break;
        case 3:
            ghost_in = &(ghost_u);
            ghost.y--;
            break;
    }
    count =(count+1)%(512);

    // ici on change entre les 2 sprites sources pour une jolie animation.
    SDL_Rect ghost_in2 = *ghost_in;
    if ((count/4)%2)
        ghost_in2.x += (constants::GHOST_WIDTH + 1);
        
    // couleur transparente
    SDL_SetColorKey(plancheSprites, true, 0);
    // copie du sprite zoomé
	SDL_BlitScaled(plancheSprites, &ghost_in2, win_surf, &ghost);
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

        // AFFICHAGE
		draw();
		SDL_UpdateWindowSurface(pWindow); 
        // LIMITE A 60 FPS
		SDL_Delay(16); // utiliser SDL_GetTicks64() pour plus de precisions
	}
    SDL_Quit(); // ON SORT
    return 0;
}
