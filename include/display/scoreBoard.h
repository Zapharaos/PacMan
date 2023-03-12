//
// Created by omar on 19/02/23.
//

#ifndef PACMAN_SCOREBOARD_H
#define PACMAN_SCOREBOARD_H
#include "extractor.h"
//#include "window.h"
#include "../utils/constants.h"
#include "../saveGame.h"
#include <SDL.h>
#include <string>

class ScoreBoard {
private :
    int width_ = 0;
    int height_ = 0;
    int score_ = 0;
    int high_score_ = 0 ;
    int lives_nb_ = 0;
    int round_nb_ = 0 ;


    std::vector <SDL_Rect> numbers_;
public:
    ScoreBoard();

    ScoreBoard(int width, int height, int score, int highScore, int livesNb, int roundNb,
               const std::vector<SDL_Rect> &numbers);

    [[nodiscard]] int getWidth() const;

    void setWidth(int width);

    [[nodiscard]] int getHeight() const;

    void setHeight(int height);

    [[nodiscard]] int getScore() const;

    void setScore(int score);

    [[nodiscard]] int getHighScore() const;

    void setHighScore(int highScore);

    [[nodiscard]] int getLivesNb() const;

    void setLivesNb(int livesNb);

    bool updateHighScore();

    void updateScore(int points);

    [[nodiscard]] int getRoundNb() const;

    void setRoundNb(int roundNb);

    //Will write "High Score on Window" another function should handle the points display
    void writeHighScoreText(SDL_Surface *win_surf , SDL_Surface *plancheSprites);


    void initNumberSprites();

    std::vector <SDL_Rect> getPointsToPrint(int points);

    //Write and update high score points
    void writeHighScorePoints(SDL_Surface *win_surf , SDL_Surface *plancheSprites,int points);

    void writeScorePoints(SDL_Surface *win_surf , SDL_Surface *plancheSprites,int points);

    int getSavedHighScore();
};


#endif //PACMAN_SCOREBOARD_H
