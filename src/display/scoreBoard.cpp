//
// Created by omar on 19/02/23.
//

#include "../../include/display/scoreBoard.h"


ScoreBoard::ScoreBoard() = default;



ScoreBoard::ScoreBoard(int width, int height, int score, int highScore, int livesNb, int roundNb,
                       const std::vector<SDL_Rect> &numbers) : width_(width), height_(height), score_(score),
                                                          high_score_(highScore), lives_nb_(livesNb),
                                                          round_nb_(roundNb), numbers_(numbers) {}



int ScoreBoard::getWidth() const {
    return width_;
}

void ScoreBoard::setWidth(int width) {
    width_ = width;
}

int ScoreBoard::getHeight() const {
    return height_;
}

void ScoreBoard::setHeight(int height) {
    height_ = height;
}


int ScoreBoard::getHighScore() const {
    return high_score_;
}

void ScoreBoard::setHighScore(int highScore) {
    high_score_ = highScore;
}

int ScoreBoard::getLivesNb() const {
    return lives_nb_;
}

void ScoreBoard::setLivesNb(int livesNb) {
    lives_nb_ = livesNb;
}

int ScoreBoard::getScore() const {
    return score_;
}

void ScoreBoard::setScore(int score) {
    score_ = score;
}

bool ScoreBoard::updateHighScore() {
    if (score_>high_score_){
        high_score_ = score_;
        return true ;
    }
    return false ;

}

int ScoreBoard::getRoundNb() const {
    return round_nb_;
}

void ScoreBoard::setRoundNb(int roundNb) {
    round_nb_ = roundNb;
}



void ScoreBoard::writeHighScoreText(SDL_Surface *win_surf , SDL_Surface *plancheSprites ) {

    initNumberSprites();
    //Get H
    SDL_Rect h_ = Extractor::extractNthElementRowFromMap(
            constants::BMP_CHARACTER_WIDTH,
            constants::BMP_CHARACTER_HEIGHT,
            7,
            constants::BMP_NUMBER_START_SECOND_ROW_X,
            constants::BMP_NUMBER_START_SECOND_ROW_Y,
            1);
    //Get I
    SDL_Rect i_ = Extractor::extractNthElementRowFromMap(
            constants::BMP_CHARACTER_WIDTH,
            constants::BMP_CHARACTER_HEIGHT,
            8,
            constants::BMP_NUMBER_START_SECOND_ROW_X,
            constants::BMP_NUMBER_START_SECOND_ROW_Y,
            1);
    //Get G
    SDL_Rect g_ = Extractor::extractNthElementRowFromMap(
            constants::BMP_CHARACTER_WIDTH,
            constants::BMP_CHARACTER_HEIGHT,
            6,
            constants::BMP_NUMBER_START_SECOND_ROW_X,
            constants::BMP_NUMBER_START_SECOND_ROW_Y,
            1);
    //Get S
    SDL_Rect s_ = Extractor::extractNthElementRowFromMap(
            constants::BMP_CHARACTER_WIDTH,
            constants::BMP_CHARACTER_HEIGHT,
            3,
            constants::BMP_NUMBER_START_THIRD_ROW_X,
            constants::BMP_NUMBER_START_THIRD_ROW_Y,
            1);
    //Get C
    SDL_Rect c_ = Extractor::extractNthElementRowFromMap(
             constants::BMP_CHARACTER_WIDTH,
             constants::BMP_CHARACTER_HEIGHT,
             2,
             constants::BMP_NUMBER_START_SECOND_ROW_X,
             constants::BMP_NUMBER_START_SECOND_ROW_Y,
             1);
    //Get O
    SDL_Rect o_ = Extractor::extractNthElementRowFromMap(
            constants::BMP_CHARACTER_WIDTH,
            constants::BMP_CHARACTER_HEIGHT,
            14,
            constants::BMP_NUMBER_START_SECOND_ROW_X,
            constants::BMP_NUMBER_START_SECOND_ROW_Y,
            1);
    //Get R
    SDL_Rect r_ = Extractor::extractNthElementRowFromMap(
            constants::BMP_CHARACTER_WIDTH,
            constants::BMP_CHARACTER_HEIGHT,
            2,
            constants::BMP_NUMBER_START_THIRD_ROW_X,
            constants::BMP_NUMBER_START_THIRD_ROW_Y,
            1);
    //Get E
    SDL_Rect e_ = Extractor::extractNthElementRowFromMap(
            constants::BMP_CHARACTER_WIDTH,
            constants::BMP_CHARACTER_HEIGHT,
            4,
            constants::BMP_NUMBER_START_SECOND_ROW_X,
            constants::BMP_NUMBER_START_SECOND_ROW_Y,
            1);

    SDL_Rect position = h_;
    position.x = constants::SCORE_BOARD_START_X ;
    position.y = constants::SCORE_BOARD_START_Y ;
    position.w = constants::BMP_CHARACTER_WIDTH * 2.5 ;
    position.h = constants::BMP_CHARACTER_HEIGHT * 2.5 ;

    int offset = position.w + 1 ;
    //write H
    SDL_BlitScaled(plancheSprites, &h_, win_surf, &position);
    //write I
    position.x += offset  ;
    SDL_BlitScaled(plancheSprites, &i_, win_surf, &position);
    //write G
    position.x += offset ;
    SDL_BlitScaled(plancheSprites, &g_, win_surf, &position);
    //write H
    position.x += offset ;
    SDL_BlitScaled(plancheSprites, &h_, win_surf, &position);
    //space
    position.x += 5 ;

    //write S
    position.x += offset ;
    SDL_BlitScaled(plancheSprites, &s_, win_surf, &position);
    //write C
    position.x += offset ;
    SDL_BlitScaled(plancheSprites, &c_, win_surf, &position);
    //write O
    position.x += offset ;
    SDL_BlitScaled(plancheSprites, &o_, win_surf, &position);
    //write R
    position.x += offset ;
    SDL_BlitScaled(plancheSprites, &r_, win_surf, &position);
    //write E
    position.x += offset ;
    SDL_BlitScaled(plancheSprites, &e_, win_surf, &position);
}

void ScoreBoard::initNumberSprites() {
    //extract from 1 to 9 ;

    numbers_ = Extractor::extractRowFromMap( constants::BMP_CHARACTER_WIDTH,
                                  constants::BMP_CHARACTER_HEIGHT,
                                  9,
                                  constants::BMP_NUMBER_START_FIRST_ROW_X,
                                  constants::BMP_NUMBER_START_FIRST_ROW_Y,
                                  1
            );

    //extract 0
    SDL_Rect sprite_zero = {constants::BMP_NUMBER_START_ZERO_ROW_X,
                       constants::BMP_NUMBER_START_FIRST_ROW_Y,
                       constants::BMP_CHARACTER_WIDTH,
                       constants::BMP_CHARACTER_HEIGHT};
    numbers_.push_back(sprite_zero);

    //0 1 2 3 4 5 6 7 8 9
}

std::vector <SDL_Rect> ScoreBoard::getPointsToPrint(int points) {

    std::string c = std::to_string(points);
    std::vector <SDL_Rect> points_to_print ;
    for(char i : c){
        if(i=='0'){
            points_to_print.push_back(numbers_[9]);
        }
        else if(i=='1'){
            points_to_print.push_back(numbers_[0]);
        }
        else if(i=='2'){
            points_to_print.push_back(numbers_[1]);
        }
        else if(i=='3'){
            points_to_print.push_back(numbers_[2]);
        }
        else if(i=='4'){
            points_to_print.push_back(numbers_[3]);
        }
        else if(i=='5'){
            points_to_print.push_back(numbers_[4]);
        }
        else if(i=='6'){
            points_to_print.push_back(numbers_[5]);
        }
        else if(i=='7'){
            points_to_print.push_back(numbers_[6]);
        }
        else if(i=='8'){
            points_to_print.push_back(numbers_[7]);
        }
        else{
            points_to_print.push_back(numbers_[8]);
        }

    }
    return points_to_print ;
}

void ScoreBoard::writeHighScorePoints(SDL_Surface *win_surf, SDL_Surface *plancheSprites, int points) {

    SDL_SetColorKey(plancheSprites, true, 0);
    std::vector <SDL_Rect>  points_to_print = getPointsToPrint(points);
    SDL_Rect position = points_to_print[0] ;
    position.x = constants::SCORE_BOARD_POINTS_START_X ;
    position.y = constants::SCORE_BOARD_POINTS_START_Y ;
    position.w = constants::BMP_CHARACTER_WIDTH * 2 ;
    position.h = constants::BMP_CHARACTER_HEIGHT * 2 ;

    int offset = constants::BMP_CHARACTER_WIDTH + 8 ;

    for (SDL_Rect s : points_to_print ){
        SDL_SetColorKey (plancheSprites,false,0);
        SDL_BlitScaled(plancheSprites, &s, win_surf, &position);
        position.x += offset ;
    }
}

void ScoreBoard::writeScorePoints(SDL_Surface *win_surf, SDL_Surface *plancheSprites, int points) {
    SDL_SetColorKey(plancheSprites, true, 0);
    std::vector <SDL_Rect>  points_to_print = getPointsToPrint(points);
    SDL_Rect position = points_to_print[0] ;
    position.x = constants::SCORE_BOARD_POINTS_START_X ;
    position.y = constants::SCORE_BOARD_POINTS_START_Y + 50;
    position.w = constants::BMP_CHARACTER_WIDTH * 2 ;
    position.h = constants::BMP_CHARACTER_HEIGHT * 2 ;

    int offset = constants::BMP_CHARACTER_WIDTH + 8 ;
    score_ = points ;

    for (SDL_Rect s : points_to_print ){
        SDL_SetColorKey (plancheSprites,false,0);
        SDL_BlitScaled(plancheSprites, &s, win_surf, &position);
        position.x += offset ;
    }
}

int ScoreBoard::getSavedHighScore() {
    high_score_ = stoi(SaveGame::getHighScore());
    return high_score_ ;
}






