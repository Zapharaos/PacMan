#include <SDL.h>

#include <iostream>
#include <memory>
#include "../include/utils/constants.h"
#include "../include/game.h"
#include "../include/saveGame.h"
#include "../include/display/window.h"

Direction last;
int tick = 1000/60;

int main(int argc, char** argv)
{
    //Save game test
    SaveGame::saveGameState(50, 50) ;
    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
		std::cerr <<"Echec de l'initialisation de la SDL " << SDL_GetError() << std::endl;
		return 1;
    }


    std::shared_ptr<Window> window_ = std::make_shared<Window> (constants::WINDOW_MAP_WIDTH,
                                                constants::WINDOW_MAP_HEIGHT,
                                                "Pacman");

    std::shared_ptr<Game> game = std::make_shared<Game>     (constants::MAP_WIDTH, constants::MAP_HEIGHT,
                                                             constants::WINDOW_CELL_HEIGHT, constants::PATH_FILE_PACMAN_MAP
                                                        , constants::LIVES);
    game->setHighScore( game->getSavedHighScore());
    window_->createWindow(game);

    // BOUCLE PRINCIPALE
	bool quit = false;
    bool paused = false;
    SDL_Event event;

    // Gestion du clavier
    int nbk;
    const Uint8* keys = SDL_GetKeyboardState(&nbk);

	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
            if(event.type == SDL_QUIT) {
                quit = true;
                break;
            } else if (event.type == SDL_KEYDOWN) {
                if(event.key.keysym.sym == SDLK_SPACE && event.key.repeat == 0)
                {
                    StatusType statusType = game->getStatus();
                    if(statusType == StatusType::RUNNING) // Pause
                        game->setStatus(StatusType::PAUSED);
                    else if(statusType == StatusType::PAUSED) // Resume
                        game->setStatus(StatusType::RUNNING);
                    paused = true;
                    break;
                }
            }
		}

        SDL_PumpEvents(); // Get keys

        // Exit
        if (keys[SDL_SCANCODE_ESCAPE])
            quit = true;

        // Movements
        if(!paused && !quit && game->getStatus() == StatusType::RUNNING) {
            if (keys[SDL_SCANCODE_LEFT])
                last = game->move(last, Direction{DirectionType::LEFT});
            else if (keys[SDL_SCANCODE_RIGHT])
                last = game->move(last, Direction{DirectionType::RIGHT});
            else if (keys[SDL_SCANCODE_UP])
                last = game->move(last, Direction{DirectionType::UP});
            else if (keys[SDL_SCANCODE_DOWN])
                last = game->move(last, Direction{DirectionType::DOWN});
            else
                game->move(last);
        }

        paused = false;

        // AFFICHAGE

        window_->drawWindow(last);
        SDL_RenderPresent(window_->getRender().get());
        //SDL_RenderPresent(windowrender.get());
        //SDL_UpdateWindowSurface(window_->getWindow().get());

        //window_.drawMapInit(game,last);



		//SDL_UpdateWindowSurface(window_.getWindow().get());
        // LIMITE A 60 FPS
		SDL_Delay(tick); // utiliser SDL_GetTicks64() pour plus de precisions
	}
    SDL_Quit(); // ON SORT
    window_->freeRessources();
    return 0;
}
