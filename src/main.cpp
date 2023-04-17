#include <SDL.h>

#include "../include/config/config.h"
#include "../include/game.h"

int main(int argc, char **argv)
{
    // Init things (that may crash) outside from the game constructor.
    Map map = Map{loadCellTypesFromFile(config::files::kMap)};
    Window window;
    window.init();
    // TODO : fix high_score to not crash when file does not exist.
    /*auto high_score = stoul(getSavedHighScore());*/
    unsigned long high_score = 0;
    Game game = Game{map, window, high_score};

    // Prepare reading user's inputs.
    int nbk;
    const Uint8 *keys = SDL_GetKeyboardState(&nbk);
    SDL_Event event;

    bool quit = false;
    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) // Exit
            {
                quit = true;
                break;
            } else if (event.type == SDL_KEYDOWN)
            {
                // Pause : "space" key repeat as a single input.
                if (event.key.keysym.sym == SDLK_SPACE && event.key.repeat == 0)
                {
                    game.togglePause();
                    break;
                }
            }
        }

        auto start = std::chrono::steady_clock::now();
        SDL_PumpEvents(); // Get keys

        // Exit game.
        if (keys[SDL_SCANCODE_ESCAPE])
            break;

        // Read user input for Pacman movement.
        Direction direction;
        if (keys[SDL_SCANCODE_LEFT])
            direction.setDirection(DirectionType::kLeft);
        else if (keys[SDL_SCANCODE_RIGHT])
            direction.setDirection(DirectionType::kRight);
        else if (keys[SDL_SCANCODE_UP])
            direction.setDirection(DirectionType::kUp);
        else if (keys[SDL_SCANCODE_DOWN])
            direction.setDirection(DirectionType::kDown);

        // Handle game & move Pacman.
        game.tick(direction);

        // Cap to 60 frames per second.
        auto finish = std::chrono::steady_clock::now() - start;
        if (config::settings::kTickTime > finish)
            SDL_Delay(std::chrono::duration_cast<std::chrono::milliseconds>(
                    config::settings::kTickTime - finish).count());
    }

    // Leave game.
    game.quit();
    return 0;
}
