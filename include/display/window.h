//
// Created by omar on 01/03/23.
//

#ifndef PACMAN_WINDOW_H
#define PACMAN_WINDOW_H

#include <utility>
#include <memory>

#include "scoreBoard.h"
#include "../config/visuals.h"

/** Game visuals. */
class Window {

private :


    /** Window title. */
    std::string title_{};

    /** Main window. */
    std::shared_ptr<SDL_Window> window_{};

    /** Bitmap surface, used for changing character colours */
    std::shared_ptr<SDL_Surface> surface_{};

    /** ScoreBoard Object. */
    ScoreBoard score_board_{};

    /** hashmap to store all characters */
    std::unordered_map<char, SDL_Rect> character_map_;


protected:

    /** Renderer to display sprites. */
    std::shared_ptr<SDL_Renderer> renderer_{};

    /** To load image t graphics hardware memory. */
    std::shared_ptr<SDL_Texture> texture_{};

    /** Window width. */
    int width_{};

    /** Window height. */
    int height_{};

public:

    const std::string &getTitle() const;

    const SDL_Rect &getGhostBlinkyR() const;

    const SDL_Rect &getGhostPinkyR() const;

    const SDL_Rect &getGhostInkyR() const;

    const SDL_Rect &getGhostClydeR() const;

    const std::shared_ptr<SDL_Renderer> &getRenderer() const;

    const std::shared_ptr<SDL_Texture> &getTexture() const;
    //TODO MOVE ALL THESE INTO VISUALS
    SDL_Rect bg_ = {constants::WINDOW_MAP_START_X, constants::WINDOW_MAP_START_Y, constants::WINDOW_MAP_WIDTH,
                    constants::WINDOW_MAP_HEIGHT}; // ici scale x4
    SDL_Rect ghost_scared = {3, 195, constants::BMP_ENTITY_GHOST_WIDTH, constants::BMP_ENTITY_GHOST_HEIGHT};

    SDL_Rect ghost_blinky_r = {constants::BMP_GHOST_BLINKY_START_X,
                               constants::BMP_GHOST_BLINKY_START_Y,
                               constants::BMP_ENTITY_GHOST_WIDTH,
                               constants::BMP_ENTITY_GHOST_HEIGHT};

    SDL_Rect ghost_pinky_r = {constants::BMP_GHOST_PINKY_START_X,
                               constants::BMP_GHOST_PINKY_START_Y,
                               constants::BMP_ENTITY_GHOST_WIDTH,
                               constants::BMP_ENTITY_GHOST_HEIGHT};

    SDL_Rect ghost_inky_r = {constants::BMP_GHOST_INKY_START_X,
                              constants::BMP_GHOST_INKY_START_Y,
                              constants::BMP_ENTITY_GHOST_WIDTH,
                              constants::BMP_ENTITY_GHOST_HEIGHT};

    SDL_Rect ghost_clyde_r = {constants::BMP_GHOST_CLYDE_START_X,
                              constants::BMP_GHOST_CLYDE_START_Y,
                              constants::BMP_ENTITY_GHOST_WIDTH,
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

    /** Initialize the window. */
    void init();

    /** Clear the window. */
    void clear();

    /** Update the window. */
    void update();

    /** Draw an entity onto the window.
     * @pre entity must have Sprite member and a getSprite() method.
     * @tparam T Type of the object to display.
     * @param entity Object to display.
     */
    template<typename T>
    inline void draw(const T &object,int offsetY) {
        auto sprite = object.getSprite();
        auto image = sprite.getImage();
        auto position = sprite.getPosition();
        position.y += offsetY ;
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

    /**
     * update and display number of lives
     * @param nb_lives
     */
    void updateLives(int nb_lives);

    /**
     * update the display the fruits and powerups
     */
    void updateFruits();

    /**
     * adds a fruit sprite into the queue in scoreboard
     * @param fruit
     */
    void addFruits(SDL_Rect fruit);

    /**
     * Initialises the hashmap containing all letters, numbers and special characters
     */
    void initSpriteMap();

    /**
     * Displays and updates the score
     * @param render
     * @param texture
     * @param points
     * @param character_map
     * @param pos_x
     * @param pos_y
     * @return
     */
    void writeScorePoints(int point, int pos_x, int pos_y, float scale, std::tuple<int, int, int> colour = colours::kWhite);

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
    void writeWord(const std::string &word, int pos_x, int pos_y,
                   int offset, float scale =  1 , std::tuple<int, int, int> colour = colours::kWhite);

};

#endif //PACMAN_WINDOW_H
