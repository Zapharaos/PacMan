#include <SDL.h>

#include <iostream>
#include "../include/utils/constants.h"
#include "../include/game.h"
#include "../include/saveGame.h"
#include "../include/utils/direction.h"
#include "../include/display/window.h"

SDL_Window* pWindow = nullptr;
SDL_Surface* win_surf = nullptr;
SDL_Surface* plancheSprites = nullptr;

SDL_Rect src_bg = { constants::BMP_MAP_START_X,constants::BMP_MAP_START_Y, constants::BMP_MAP_WIDTH,constants::BMP_MAP_HEIGHT }; // x,y, w,h (0,0) en haut a gauche
SDL_Rect bg = { constants::WINDOW_MAP_START_X,constants::WINDOW_MAP_START_Y, constants::WINDOW_MAP_WIDTH,constants::WINDOW_MAP_HEIGHT }; // ici scale x4

SDL_Rect ghost_scared = { 3,195, constants::BMP_ENTITY_GHOST_WIDTH,constants::BMP_ENTITY_GHOST_HEIGHT };
SDL_Rect ghost_blinky_r = { constants::BMP_GHOST_BLINKY_START_X + constants::BMP_ENTITY_GHOST_OFFSET_TO_RIGHT_IMG,constants::BMP_GHOST_BLINKY_START_Y, constants::BMP_ENTITY_GHOST_WIDTH,constants::BMP_ENTITY_GHOST_HEIGHT };
SDL_Rect ghost_blinky_l = { constants::BMP_GHOST_BLINKY_START_X + constants::BMP_ENTITY_GHOST_OFFSET_TO_LEFT_IMG,constants::BMP_GHOST_BLINKY_START_Y, constants::BMP_ENTITY_GHOST_WIDTH,constants::BMP_ENTITY_GHOST_HEIGHT };
SDL_Rect ghost_blinky_u = { constants::BMP_GHOST_BLINKY_START_X + constants::BMP_ENTITY_GHOST_OFFSET_TO_UP_IMG,constants::BMP_GHOST_BLINKY_START_Y, constants::BMP_ENTITY_GHOST_WIDTH,constants::BMP_ENTITY_GHOST_HEIGHT };
SDL_Rect ghost_blinky_d = { constants::BMP_GHOST_BLINKY_START_X + constants::BMP_ENTITY_GHOST_OFFSET_TO_DOWN_IMG,constants::BMP_GHOST_BLINKY_START_Y, constants::BMP_ENTITY_GHOST_WIDTH,constants::BMP_ENTITY_GHOST_HEIGHT };
SDL_Rect ghost_blinky = { 32,32, constants::WINDOW_CELL_WIDTH,constants::WINDOW_CELL_HEIGHT };     // ici scale x2

int count_;
Game* game = nullptr;
Direction last;


int main(int argc, char** argv)
{
    //Save game test
    SaveGame::saveGameState(50, 50) ;
    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
		std::cerr <<"Echec de l'initialisation de la SDL " << SDL_GetError() << std::endl;
		return 1;
    }

	//init();
    Window window_ = *new Window("Title");
    game = new Game(constants::MAP_WIDTH, constants::MAP_HEIGHT,
                    constants::WINDOW_CELL_HEIGHT, constants::PATH_FILE_PACMAN_MAP
                    , constants::LIVES);
    window_.createWindow();


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

        if (keys[SDL_SCANCODE_ESCAPE])
            quit = true;

        if (keys[SDL_SCANCODE_LEFT])
            last = game->move(last, {DirectionType::LEFT, true});
        else if (keys[SDL_SCANCODE_RIGHT])
            last = game->move(last, {DirectionType::RIGHT, false});
        else if (keys[SDL_SCANCODE_UP])
            last = game->move(last, {DirectionType::UP, true});
        else if (keys[SDL_SCANCODE_DOWN])
            last = game->move(last, {DirectionType::DOWN, false});
        else
            game->move(last);

        // AFFICHAGE
		//draw();
        window_.drawWindow(game,last);
		SDL_UpdateWindowSurface(window_.getPWindow());
        // LIMITE A 60 FPS
		SDL_Delay(1000/60); // utiliser SDL_GetTicks64() pour plus de precisions
	}
    SDL_Quit(); // ON SORT
    return 0;
}
