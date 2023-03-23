//
// Created by omar on 19/02/23.
//
#ifndef PACMAN_SCOREBOARD_H
#define PACMAN_SCOREBOARD_H

#include <SDL.h>
#include <string>
#include <memory>
#include <queue>
#include "../config/constants.h"
#include "../utils/utils.h"
#include "../config/init_sprites.h"


/**
 * Score Board display
 */
class ScoreBoard {
private :
    // Window width
    int width_ = constants::SCORE_BOARD_WIDTH;
    //Window Height
    int height_ = 0 ;
    //Fruit queue
    std::vector<SDL_Rect> fruit_queue_ ;

    // Vector that will hold sprites of all numbers (0 - 9)
    std::vector <SDL_Rect> numbers_;
public:

    ScoreBoard();

    ScoreBoard(int width, int height, std::vector<SDL_Rect> numbers);

    /////////// Getters and setters ///////////

    [[nodiscard]] int getWidth() const;




    /**
     * getPointsToPrint
     * Sets a vector with the sprites to print
     * @param points
     * @return vector containing sprites
     */
    std::vector <SDL_Rect> getPointsToPrint(int points,const std::unordered_map<char, SDL_Rect>& character_map);

    /**
     * Used to display lives remaining
     * @param render
     * @param texture
     * @param livesNb
     */
    void writeLives(const std::shared_ptr<SDL_Renderer>& render,
                    const std::shared_ptr<SDL_Texture>& texture,
                    int livesNb);
    /**
     * Used to display fruits and powerups
     * @param render
     * @param texture
     */
    void updateFruits(const std::shared_ptr<SDL_Renderer>& render,
                     const std::shared_ptr<SDL_Texture>& texture);
    /**
     * Add a fruit to the queue of fruits to display
     * @param fruit
     */
    void addFruits(SDL_Rect fruit) ;
};


#endif //PACMAN_SCOREBOARD_H
