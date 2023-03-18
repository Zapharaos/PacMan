//
// Created by omar on 01/03/23.
//

#ifndef PACMAN_WINDOW_H
#define PACMAN_WINDOW_H


#include <utility>
#include <memory>
#include "scoreBoard.h"
#include "../utils/utils.h"

/** Game visuals. */
class Window {

private :

    /** Window width. */
    int width_{} ;

    /** Window height. */
    int height_{} ;

    /** Window title. */
    string title_ {};

    /** Main window. */
    shared_ptr<SDL_Window> window_ {};

    /** Window surface. */
    shared_ptr<SDL_Surface> win_surf_ {};

    /** Sprites file. */
    shared_ptr<SDL_Surface> plancheSprites_ {};

    /** Renderer to display sprites. */
    shared_ptr<SDL_Renderer> render_ {};

    /** To load image t graphics hardware memory. */
    shared_ptr<SDL_Texture> texture_ {};

    /** ScoreBoard Object. */
    ScoreBoard scoreBoard_ {};

public:

    SDL_Rect bg_ = { constants::WINDOW_MAP_START_X,constants::WINDOW_MAP_START_Y, constants::WINDOW_MAP_WIDTH,constants::WINDOW_MAP_HEIGHT }; // ici scale x4
    SDL_Rect ghost_scared = { 3,195, constants::BMP_ENTITY_GHOST_WIDTH,constants::BMP_ENTITY_GHOST_HEIGHT };
    SDL_Rect ghost_blinky_r = { constants::BMP_GHOST_BLINKY_START_X + constants::BMP_ENTITY_GHOST_OFFSET_TO_RIGHT_IMG,constants::BMP_GHOST_BLINKY_START_Y, constants::BMP_ENTITY_GHOST_WIDTH,constants::BMP_ENTITY_GHOST_HEIGHT };
    SDL_Rect ghost_blinky_l = { constants::BMP_GHOST_BLINKY_START_X + constants::BMP_ENTITY_GHOST_OFFSET_TO_LEFT_IMG,constants::BMP_GHOST_BLINKY_START_Y, constants::BMP_ENTITY_GHOST_WIDTH,constants::BMP_ENTITY_GHOST_HEIGHT };
    SDL_Rect ghost_blinky_u = { constants::BMP_GHOST_BLINKY_START_X + constants::BMP_ENTITY_GHOST_OFFSET_TO_UP_IMG,constants::BMP_GHOST_BLINKY_START_Y, constants::BMP_ENTITY_GHOST_WIDTH,constants::BMP_ENTITY_GHOST_HEIGHT };
    SDL_Rect ghost_blinky_d = { constants::BMP_GHOST_BLINKY_START_X + constants::BMP_ENTITY_GHOST_OFFSET_TO_DOWN_IMG,constants::BMP_GHOST_BLINKY_START_Y, constants::BMP_ENTITY_GHOST_WIDTH,constants::BMP_ENTITY_GHOST_HEIGHT };
    SDL_Rect ghost_blinky = { 32,32, constants::WINDOW_CELL_WIDTH,constants::WINDOW_CELL_HEIGHT };     // ici scale x2

    /** Default Window constructor. */
    Window();

    /** Window constructor.
     *
     * @param width Window width.
     * @param height Window height.
     * @param title Window title.
     */
    Window(int width, int height, string title);

    /** Initialize the window. */
    void init();

    /** Clear the window. */
    void clear();

    /** Update the window. */
    void update();

    /** Draw an entity onto the window. */
    template<typename T>
    inline void draw(const T &entity)
    {
        SDL_Rect image = entity.getSpriteImage();
        SDL_Rect position = entity.getSpritePosition();
        SDL_RenderCopy(render_.get(), texture_.get(), &image, &position);
    }

    void writeHighScore();

    void updateHighScore(int points);

    /** Free the window members. */
    void free();
};


#endif //PACMAN_WINDOW_H
