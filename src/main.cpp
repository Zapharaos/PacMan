#include <SDL.h>

#include "../include/config/constants.h"
#include "../include/game.h"

int main(int argc, char **argv)
{
    Map map = Map{constants::MAP_WIDTH, constants::MAP_HEIGHT,
                  constants::WINDOW_CELL_HEIGHT, loadCellTypesFromFile(constants::PATH_FILE_PACMAN_MAP)};
    Window window = Window{constants::WINDOW_MAP_WIDTH, constants::WINDOW_MAP_HEIGHT, "Pacman"};
    Game game = Game{map, window, constants::LIVES};

    bool quit = false;
    std::chrono::milliseconds tickTime(1000 / 60);

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

        auto start = std::chrono::steady_clock::now();
        SDL_PumpEvents(); // Get keys
        Direction direction;

        // Exit
        if (keys[SDL_SCANCODE_ESCAPE])
            quit = true;

        // Movements
        if (keys[SDL_SCANCODE_LEFT])
            direction.setDirection(DirectionType::kLeft);
        else if (keys[SDL_SCANCODE_RIGHT])
            direction.setDirection(DirectionType::kRight);
        else if (keys[SDL_SCANCODE_UP])
            direction.setDirection(DirectionType::kUp);
        else if (keys[SDL_SCANCODE_DOWN])
            direction.setDirection(DirectionType::kDown);

        // Handle game
        game.tick(direction);

        // Cap to 60 frames per second.
        auto finish = std::chrono::steady_clock::now() - start;
        if (tickTime > finish)
            SDL_Delay(std::chrono::duration_cast<std::chrono::milliseconds>(
                    tickTime - finish).count());
    }

    // Save high score.
    // TODO : write high score to file

    // Leave game.
    SDL_Quit();
    game.quit();
    return 0;
}
