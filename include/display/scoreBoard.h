//
// Created by omar on 19/02/23.
//

#ifndef PACMAN_SCOREBOARD_H
#define PACMAN_SCOREBOARD_H
#include "extractor.h"
#include "../utils/constants.h"
#include "../utils/utils.h"
#include "../saveGame.h"
#include <SDL.h>
#include <string>
#include <memory>

/**
 * Score Board display
 */
class ScoreBoard {
private :
    // Window width
    int width_ = constants::SCORE_BOARD_WIDTH;
    //Window Height
    int height_ = 0 ;


    // Vector that will hold sprites of all numbers (0 - 9)
    std::vector <SDL_Rect> numbers_;
public:

    ScoreBoard();

    ScoreBoard(int width, int height, const vector<SDL_Rect> &numbers);

    /////////// Getters and setters ///////////

    [[nodiscard]] int getWidth() const;


    /**
     * writeHighScoreText
     * Will write "High Score" on the scoreboard window
     * @param win_surf
     * @param plancheSprites
     */
     void writeHighScoreText(  const shared_ptr<SDL_Renderer>& render,
                               const shared_ptr<SDL_Texture>& texture);

    /**
     * initNumberSprites
     * Will get all number sprites from the bitmap and store them in numbers_
     */
    void initNumberSprites();

    /**
     * getPointsToPrint
     * Sets a vector with the sprites to print
     * @param points
     * @return vector containing sprites
     */
    std::vector <SDL_Rect> getPointsToPrint(int points);

/**
* writeHighScorePoints
* Write and update high score points
 * @param render
 * @param texture
 * @param points
 */
    void writeHighScorePoints(  const shared_ptr<SDL_Renderer>& render,
                                const shared_ptr<SDL_Texture>& texture,
                                int points);

/**
 *  Write and update score points
 * @param render
 * @param texture
 * @param points
 */
    void writeScorePoints(  const shared_ptr<SDL_Renderer>& render,
                            const shared_ptr<SDL_Texture>& texture,
                            int points);
    /**
     * getSavedHighScore
     * Gets the high score set locally from the save.json file
     * @return high_score_
     */
    int getSavedHighScore();
};


#endif //PACMAN_SCOREBOARD_H
