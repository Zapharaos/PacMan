//
// Created by omar on 19/02/23.
//

#include "../include/scoreBoard.h"

scoreBoard::scoreBoard() = default;

int scoreBoard::getWidth() const {
    return width_;
}

void scoreBoard::setWidth(int width) {
    width_ = width;
}

int scoreBoard::getHeight() const {
    return height_;
}

void scoreBoard::setHeight(int height) {
    height_ = height;
}


int scoreBoard::getHighScore() const {
    return high_score_;
}

void scoreBoard::setHighScore(int highScore) {
    high_score_ = highScore;
}

int scoreBoard::getLivesNb() const {
    return lives_nb_;
}

void scoreBoard::setLivesNb(int livesNb) {
    lives_nb_ = livesNb;
}

int scoreBoard::getScore() const {
    return score_;
}

void scoreBoard::setScore(int score) {
    score_ = score;
}

void scoreBoard::updateHighScore() {
    if (score_>high_score_){
        high_score_ = score_;
    }
}

void scoreBoard::updateScore(int points) {
    score_+=points;
}

scoreBoard::scoreBoard(int width, int height, int score, int highScore, int livesNb, int roundNb) : width_(width),
                                                                                                    height_(height),
                                                                                                    score_(score),
                                                                                                    high_score_(
                                                                                                            highScore),
                                                                                                    lives_nb_(livesNb),
                                                                                                    round_nb_(
                                                                                                            roundNb) {}

int scoreBoard::getRoundNb() const {
    return round_nb_;
}

void scoreBoard::setRoundNb(int roundNb) {
    round_nb_ = roundNb;
}





