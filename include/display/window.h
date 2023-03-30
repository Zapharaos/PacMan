//
// Created by omar on 01/03/23.
//

#ifndef PACMAN_WINDOW_H
#define PACMAN_WINDOW_H

#include <utility>
#include <memory>

#include "scoreBoard.h"

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

    // TODO : remove
    SDL_Rect bg_ = { 0,0, config::dimensions::kWindowWidth,config::dimensions::kWindowHeight };

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
    inline void draw(const T &object) {
        auto sprite = object.getSprite();
        auto image = sprite.getImage();
        auto position = sprite.getPosition();
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
