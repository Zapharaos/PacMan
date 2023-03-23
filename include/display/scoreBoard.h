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
     * writeHighScoreText
     * Will write "High Score" on the scoreboard window
     * @param win_surf
     * @param plancheSprites
     */
     void writeHighScoreText(  const std::shared_ptr<SDL_Renderer>& render,
                               const std::shared_ptr<SDL_Texture>& texture,
                               const std::unordered_map<char, SDL_Rect>& character_map);

    /**
     * getPointsToPrint
     * Sets a vector with the sprites to print
     * @param points
     * @return vector containing sprites
     */
    std::vector <SDL_Rect> getPointsToPrint(int points,const std::unordered_map<char, SDL_Rect>& character_map);

/**
* writeHighScorePoints
* Write and update high score points
 * @param render
 * @param texture
 * @param points
 */
    void writeHighScorePoints(  const std::shared_ptr<SDL_Renderer>& render,
                                const std::shared_ptr<SDL_Texture>& texture,
                                int points,const std::unordered_map<char, SDL_Rect>& character_map);

/**
 *  Write and update score points
 * @param render
 * @param texture
 * @param points
 */
    void writeScorePoints(  const std::shared_ptr<SDL_Renderer>& render,
                            const std::shared_ptr<SDL_Texture>& texture,
                            int points,const std::unordered_map<char, SDL_Rect>& character_map);
/**
* drawObject
* Draws desired sprite in a location
* @param src
* @param dst
* @param src_rect
* @param dst_rect
*
*/
    void drawObject( std::shared_ptr<SDL_Renderer> render
            , std::shared_ptr<SDL_Texture> texture
            , SDL_Rect src_rect
            , SDL_Rect dst_rect  );
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
