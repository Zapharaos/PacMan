//
// Created by omar on 01/03/23.
//

#ifndef PACMAN_WINDOW_H
#define PACMAN_WINDOW_H

#include <utility>
#include <memory>

#include "scoreBoard.h"
//#include "../utils/utils.h"

/** Game visuals. */
class Window {

private :

    /** Window width. */
    int width_{};

    /** Window height. */
    int height_{};

    /** Window title. */
    std::string title_{};

    /** Main window. */
    std::shared_ptr<SDL_Window> window_{};

    /** Renderer to display sprites. */
    std::shared_ptr<SDL_Renderer> renderer_{};

    /** To load image t graphics hardware memory. */
    std::shared_ptr<SDL_Texture> texture_{};

    /** ScoreBoard Object. */
    ScoreBoard score_board_{};

    /** hashmap to store all characters */
    std::unordered_map<char, SDL_Rect> character_map_;
public:

    SDL_Rect bg_ = {constants::WINDOW_MAP_START_X, constants::WINDOW_MAP_START_Y, constants::WINDOW_MAP_WIDTH,
                    constants::WINDOW_MAP_HEIGHT}; // ici scale x4
    SDL_Rect ghost_scared = {3, 195, constants::BMP_ENTITY_GHOST_WIDTH, constants::BMP_ENTITY_GHOST_HEIGHT};
    SDL_Rect ghost_blinky_r = {constants::BMP_GHOST_BLINKY_START_X + constants::BMP_ENTITY_GHOST_OFFSET_TO_RIGHT_IMG,
                               constants::BMP_GHOST_BLINKY_START_Y, constants::BMP_ENTITY_GHOST_WIDTH,
                               constants::BMP_ENTITY_GHOST_HEIGHT};
    SDL_Rect ghost_blinky_l = {constants::BMP_GHOST_BLINKY_START_X + constants::BMP_ENTITY_GHOST_OFFSET_TO_LEFT_IMG,
                               constants::BMP_GHOST_BLINKY_START_Y, constants::BMP_ENTITY_GHOST_WIDTH,
                               constants::BMP_ENTITY_GHOST_HEIGHT};
    SDL_Rect ghost_blinky_u = {constants::BMP_GHOST_BLINKY_START_X + constants::BMP_ENTITY_GHOST_OFFSET_TO_UP_IMG,
                               constants::BMP_GHOST_BLINKY_START_Y, constants::BMP_ENTITY_GHOST_WIDTH,
                               constants::BMP_ENTITY_GHOST_HEIGHT};
    SDL_Rect ghost_blinky_d = {constants::BMP_GHOST_BLINKY_START_X + constants::BMP_ENTITY_GHOST_OFFSET_TO_DOWN_IMG,
                               constants::BMP_GHOST_BLINKY_START_Y, constants::BMP_ENTITY_GHOST_WIDTH,
                               constants::BMP_ENTITY_GHOST_HEIGHT};
    SDL_Rect ghost_blinky = {32, 32, constants::WINDOW_CELL_WIDTH, constants::WINDOW_CELL_HEIGHT};     // ici scale x2

    /** Default Window constructor. */
    Window();

    /** Window constructor.
     *
     * @param width Window width.
     * @param height Window height.
     * @param title Window title.
     */
    Window(int width, int height, std::string title);

    /** Initialize the window. */
    void init();

    /** Clear the window. */
    void clear();

    /** Update the window. */
    void update();

    /** Draw an entity onto the window. */
    template<typename T>
    inline void draw(const T &entity) {
        SDL_Rect image = entity.getSpriteImage();
        SDL_Rect position = entity.getSpritePosition();
        SDL_RenderCopy(renderer_.get(), texture_.get(), &image, &position);
    }

    /**
     * display the highscore text
     */
    void writeHighScore();

    /**
     * update and display the highscore
     * @param points
     */
    void updateHighScore(int points);

    /**
     * update and display current score
     * @param score
     */
    void updateScore(int score);

    /** Free the window members. */
    void free();

    /**
     * update and display number of lives
     * @param nb_lives
     */
    void updateLives(int nb_lives);


     /**
     * writeHighScoreText
     * Will write "High Score" on the  window
      * @param pos_x
      * @param pos_y
      */
    void writeHighScoreText(int pos_x, int pos_y);

    /**
     * update the display the fruits and powerups
     */
    void updateFruits();

    /**
     * adds a fruit sprite into the queue in scoreboard
     * @param fruit
     */
    void addFruits(SDL_Rect fruit);

    void initSpriteMap();

/**
 *
 * @param render
 * @param texture
 * @param points
 * @param character_map
 * @param pos_x
 * @param pos_y
 * @return
 */
    void writeScorePoints(int point, int pos_x, int pos_y);
    /**
     * Writes a word at a given position and size
     * @param word
     * @param pos_x
     * @param pos_y
     * @param w
     * @param h
     * @param offset
     * @param colour
     */
    void writeWord(const std::string &word, int pos_x, int pos_y, int w, int h,
              int offset, std::tuple<int, int, int> colour = {252, 252, 252});
};
#endif //PACMAN_WINDOW_H
