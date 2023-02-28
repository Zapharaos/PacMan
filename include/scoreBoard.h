//
// Created by omar on 19/02/23.
//

#ifndef PACMAN_SCOREBOARD_H
#define PACMAN_SCOREBOARD_H


class scoreBoard {
private :
    int width_ = 0;
    int height_ = 0;
    int score_ = 0;
    int high_score_ = 0 ;
    int lives_nb_ = 0;
    int round_nb_ = 0 ;
public:
    scoreBoard();

    scoreBoard(int width, int height, int score, int highScore, int livesNb, int roundNb);

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

    void updateHighScore();

    void updateScore(int points);

    [[nodiscard]] int getRoundNb() const;

    void setRoundNb(int roundNb);
};


#endif //PACMAN_SCOREBOARD_H
