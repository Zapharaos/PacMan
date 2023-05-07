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

    /** hashmap to store all point sprites */
    std::unordered_map<unsigned long, SDL_Rect> points_map_;


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
    /** Map containing points from eaten ghosts and fruits to display  */
    const std::unordered_map<unsigned long, SDL_Rect> &getPointsMap() const;

    /**Renderer used by SDL */
    const std::shared_ptr<SDL_Renderer> &getRenderer() const;

    /**Texture used by SDL */
    const std::shared_ptr<SDL_Texture> &getTexture() const;

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
    inline void draw(const T &object, int offsetY) {
        auto sprite = object.getSprite();
        auto image = sprite.getImage();
        auto position = sprite.getPosition();
        position.y += offsetY;
        SDL_RenderCopy(renderer_.get(), texture_.get(), &image, &position);
    }

    /** Draw an entity onto the window.
     * @pre entity must have Sprite member and a getSprite() method.
     * @tparam T Type of the object to display.
     * @param entity Object to display.
     */
    template<typename T>
    inline void draw(const std::shared_ptr<T> &object, int offsetY) {
        draw(*object, offsetY);
    }

    /**
     * @Brief display the highscore text
     */
    void writeHighScore();

    /**
     * @Brief update and display the highscore
     * @param points number to display
     */
    void updateHighScore(unsigned long points);

    /**
     * @Brief update and display current score
     * @param score number to display
     */
    void updateScore(unsigned long score);

    /**
     * @brief update and display number of lives
     * @param nb_lives nb of lives to display
     */
    void updateLives(int nb_lives);

    /**
     * update the display the fruits and powerups in the scorebaord
     */
    void updateFruits();

    /**
     * @brief adds a fruit sprite into the queue in scoreboard
     * @param fruit fruit sprite to display and add to scoreboard
     */
    void addFruits(SDL_Rect fruit);

    /**
     * Initialises the hashmap containing all letters, numbers and special characters
     */
    void initSpriteMap();

    /**
     * @Brief Writes an integer, used to update score and highscore
     * @param point number to display
     * @param pos_x X pos on where to display
     * @param pos_y Y pos on where to display
     * @param scale scale used for display
     * @param colour colour used to display
     */
    void writeScorePoints(unsigned long point, int pos_x, int pos_y, float scale,
                          std::tuple<int, int, int> colour = colours::kWhite);

    /**
     * Writes a word at a given position and size
     * @param word Word to display
     * @param pos_x X pos on where to display
     * @param pos_y Y pos on where to display
     * @param offset Space between characters
     * @param scale scale used for display
     * @param colour colour used to display
     */
    void writeWord(const std::string &word, int pos_x, int pos_y,
                   int offset, float scale = 1, std::tuple<int, int, int> colour = colours::kWhite);

    /**
     * centerImage
     * Centers the sprite so the x coordinate is the center
     * @param src source image
     * @param x initial position
     * @return
     */
    static int centerImage(SDL_Rect src, int x);

    /**
     * Closes and quits all SDL related elements
     */
    void quit();
};

#endif //PACMAN_WINDOW_H
