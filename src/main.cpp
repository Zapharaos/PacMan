#include <SDL.h>

#include "../include/utils/constants.h"
#include "../include/game.h"

int main(int argc, char **argv)
{
    Game game = Game{constants::MAP_WIDTH, constants::MAP_HEIGHT,
                     constants::WINDOW_CELL_HEIGHT,
                     constants::PATH_FILE_PACMAN_MAP, constants::LIVES};

    bool quit = false;
    chrono::milliseconds tickTime(1000 / 60);

    int nbk;
    const Uint8 *keys = SDL_GetKeyboardState(&nbk);
    SDL_Event event;

    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
                break;
            } else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_SPACE && event.key.repeat == 0)
                {
                    game.togglePause();
                    break;
                }
            }
        }

        auto start = chrono::steady_clock::now();
        SDL_PumpEvents(); // Get keys
        Direction direction;

        // Exit
        if (keys[SDL_SCANCODE_ESCAPE])
            quit = true;

        // Movements
        if (keys[SDL_SCANCODE_LEFT])
            direction.setDirection(DirectionType::LEFT);
        else if (keys[SDL_SCANCODE_RIGHT])
            direction.setDirection(DirectionType::RIGHT);
        else if (keys[SDL_SCANCODE_UP])
            direction.setDirection(DirectionType::UP);
        else if (keys[SDL_SCANCODE_DOWN])
            direction.setDirection(DirectionType::DOWN);

        // Handle game
        game.tick(direction);

        // Cap to 60 frames per second.
        auto finish = chrono::steady_clock::now() - start;
        if (tickTime > finish)
            SDL_Delay(chrono::duration_cast<chrono::milliseconds>(
                    tickTime - finish).count());
    }

    // Save high score.
    // TODO : write high score to file

    // Leave game.
    SDL_Quit();
    game.quit();
    return 0;
}
