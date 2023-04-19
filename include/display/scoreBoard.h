//
// Created by omar on 19/02/23.
//
#ifndef PACMAN_SCOREBOARD_H
#define PACMAN_SCOREBOARD_H

#include <SDL.h>
#include <string>
#include <memory>

#include <queue>
#include "../utils/utils.h"
#include "../config/config.h"
#include "../config/visuals.h"

/**
 * Score Board display
 */
class ScoreBoard {
private :
    // Window width
    int width_ = config::dimensions::kWindowWidth;
    //Window Height
    int height_ = 0 ;
    //Fruit queue
    std::vector<SDL_Rect> fruit_queue_ ;

    // Vector that will hold sprites of all numbers (0 - 9)
    std::vector <SDL_Rect> numbers_;
public:

    ScoreBoard();

    /**
     * getPointsToPrint
     * Sets a vector with the sprites to print
     * @param points
     * @return vector containing sprites
     */
    static std::vector <SDL_Rect> getPointsToPrint(unsigned long points,const std::unordered_map<char, SDL_Rect>& character_map);

    /**
     * writeLives
     * @Brief Used to display lives remaining on scoreboard
     * @param render
     * @param texture
     * @param livesNb number of lives
     */
    static void writeLives(const std::shared_ptr<SDL_Renderer>& render,
                    const std::shared_ptr<SDL_Texture>& texture,
                    int livesNb);
    /**
     * @Brief Used to display fruits and powerups on scoreboard
     * @param render
     * @param texture
     */
    void updateFruits(const std::shared_ptr<SDL_Renderer>& render,
                     const std::shared_ptr<SDL_Texture>& texture);

    /**
     * addFruits
     * @BriefAdd a fruit to the queue of fruits to display
     * @param fruit fruit to add
     */
    void addFruits(SDL_Rect fruit) ;
};


#endif //PACMAN_SCOREBOARD_H
