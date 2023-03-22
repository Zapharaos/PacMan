//
// Created by omar on 19/02/23.
//

#include "../../include/display/scoreBoard.h"

#include <utility>

ScoreBoard::ScoreBoard() = default;

ScoreBoard::ScoreBoard(int width, int height, std::vector<SDL_Rect> numbers) : width_(width), height_(height),
                                                                               numbers_(std::move(numbers)) {}

void ScoreBoard::writeHighScoreText( const std::shared_ptr<SDL_Renderer>& render,
                                     const std::shared_ptr<SDL_Texture>& texture) {
    initNumberSprites();
    //Get H
    SDL_Rect h_ = extractNthElementRowFromMap(
            constants::BMP_CHARACTER_WIDTH,
            constants::BMP_CHARACTER_HEIGHT,
            7,
            constants::BMP_NUMBER_START_SECOND_ROW_X,
            constants::BMP_NUMBER_START_SECOND_ROW_Y,
            constants::OFFSET_CHAR);
    //Get I
    SDL_Rect i_ = extractNthElementRowFromMap(
            constants::BMP_CHARACTER_WIDTH,
            constants::BMP_CHARACTER_HEIGHT,
            8,
            constants::BMP_NUMBER_START_SECOND_ROW_X,
            constants::BMP_NUMBER_START_SECOND_ROW_Y,
            constants::OFFSET_CHAR);
    //Get G
    SDL_Rect g_ = extractNthElementRowFromMap(
            constants::BMP_CHARACTER_WIDTH,
            constants::BMP_CHARACTER_HEIGHT,
            6,
            constants::BMP_NUMBER_START_SECOND_ROW_X,
            constants::BMP_NUMBER_START_SECOND_ROW_Y,
            constants::OFFSET_CHAR);
    //Get S
    SDL_Rect s_ = extractNthElementRowFromMap(
            constants::BMP_CHARACTER_WIDTH,
            constants::BMP_CHARACTER_HEIGHT,
            3,
            constants::BMP_NUMBER_START_THIRD_ROW_X,
            constants::BMP_NUMBER_START_THIRD_ROW_Y,
            constants::OFFSET_CHAR);
    //Get C
    SDL_Rect c_ = extractNthElementRowFromMap(
            constants::BMP_CHARACTER_WIDTH,
            constants::BMP_CHARACTER_HEIGHT,
            2,
            constants::BMP_NUMBER_START_SECOND_ROW_X,
            constants::BMP_NUMBER_START_SECOND_ROW_Y,
            constants::OFFSET_CHAR);
    //Get O
    SDL_Rect o_ = extractNthElementRowFromMap(
            constants::BMP_CHARACTER_WIDTH,
            constants::BMP_CHARACTER_HEIGHT,
            14,
            constants::BMP_NUMBER_START_SECOND_ROW_X,
            constants::BMP_NUMBER_START_SECOND_ROW_Y,
            constants::OFFSET_CHAR);
    //Get R
    SDL_Rect r_ = extractNthElementRowFromMap(
            constants::BMP_CHARACTER_WIDTH,
            constants::BMP_CHARACTER_HEIGHT,
            2,
            constants::BMP_NUMBER_START_THIRD_ROW_X,
            constants::BMP_NUMBER_START_THIRD_ROW_Y,
            constants::OFFSET_CHAR);
    //Get E
    SDL_Rect e_ = extractNthElementRowFromMap(
            constants::BMP_CHARACTER_WIDTH,
            constants::BMP_CHARACTER_HEIGHT,
            4,
            constants::BMP_NUMBER_START_SECOND_ROW_X,
            constants::BMP_NUMBER_START_SECOND_ROW_Y,
            constants::OFFSET_CHAR);

    SDL_Rect position = h_;
    position.x = constants::SCORE_BOARD_START_X ;
    position.y = constants::SCORE_BOARD_START_Y ;
    position.w = constants::BMP_CHARACTER_WIDTH * 2.5 ;
    position.h = constants::BMP_CHARACTER_HEIGHT * 2.5 ;

    int offset = position.w + 1 ;
    //write H
    drawObject(render,texture, h_, position);
    //write I
    position.x += offset  ;
    drawObject(render,texture,i_,position);
    //write G
    position.x += offset ;
    drawObject(render,texture, g_, position);
    //write H
    position.x += offset ;
    drawObject(render,texture, h_, position);
    //space
    position.x += 5 ;

    //write S
    position.x += offset ;
    drawObject(render,texture, s_, position);
    //write C
    position.x += offset ;
    drawObject(render,texture, c_,  position);
    //write O
    position.x += offset ;
    drawObject(render,texture, o_,  position);
    //write R
    position.x += offset ;
    drawObject(render,texture, r_, position);
    //write E
    position.x += offset ;
    drawObject(render,texture, e_, position);
}

void ScoreBoard::initNumberSprites() {
    //extract from 1 to 9 ;

    numbers_ = extractRowFromMap( constants::BMP_CHARACTER_WIDTH,
                                  constants::BMP_CHARACTER_HEIGHT,
                                  9,
                                  constants::BMP_NUMBER_START_FIRST_ROW_X,
                                  constants::BMP_NUMBER_START_FIRST_ROW_Y,
                                  constants::OFFSET_CHAR
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

void ScoreBoard::writeHighScorePoints(  const std::shared_ptr<SDL_Renderer>& render,
                                        const std::shared_ptr<SDL_Texture>& texture,
                                        int points) {

    std::vector <SDL_Rect>  points_to_print = getPointsToPrint(points);
    SDL_Rect position = points_to_print[0] ;
    position.x = constants::SCORE_BOARD_POINTS_START_X ;
    position.y = constants::SCORE_BOARD_POINTS_START_Y ;
    position.w = constants::BMP_CHARACTER_WIDTH * 2 ;
    position.h = constants::BMP_CHARACTER_HEIGHT * 2 ;

    int offset = constants::BMP_CHARACTER_WIDTH + 8 ;

    for (SDL_Rect s : points_to_print ){
        // SDL_BlitScaled(plancheSprites.get(), &s, win_surf.get(), &position);
        drawObject(render,texture,s,position);
        position.x += offset ;
    }
}

void ScoreBoard::writeScorePoints(const std::shared_ptr<SDL_Renderer>& render,
                                  const std::shared_ptr<SDL_Texture>& texture,
                                  int points) {
    std::vector <SDL_Rect>  points_to_print = getPointsToPrint(points);
    SDL_Rect position = points_to_print[0] ;
    position.x = constants::SCORE_BOARD_POINTS_START_X ;
    position.y = constants::SCORE_BOARD_POINTS_START_Y + 50;
    position.w = constants::BMP_CHARACTER_WIDTH * 2 ;
    position.h = constants::BMP_CHARACTER_HEIGHT * 2 ;

    int offset = constants::BMP_CHARACTER_WIDTH + 8 ;

    for (SDL_Rect s : points_to_print ){
        drawObject(render,texture,s,position);
        position.x += offset ;
    }
}

int ScoreBoard::getWidth() const {
    return width_;
}

void
ScoreBoard::drawObject(std::shared_ptr<SDL_Renderer> render, std::shared_ptr<SDL_Texture> texture, SDL_Rect src_rect,
                       SDL_Rect dst_rect) {
    SDL_RenderCopy(render.get(), texture.get(), &src_rect, &dst_rect);
}



void ScoreBoard::writeLives(const std::shared_ptr<SDL_Renderer>& render,
                            const std::shared_ptr<SDL_Texture>& texture,
                            int livesNb) {
    SDL_Rect life_sprite = {
            constants::BMP_PACMAN_SCORE_BOARD_START_X ,
            constants::BMP_PACMAN_SCORE_BOARD_START_Y ,
            constants::BMP_PACMAN_SCORE_BOARD_WIDTH,
            constants::BMP_PACMAN_SCORE_BOARD_HEIGHT
    };
    SDL_Rect lives_start ;
    lives_start.w = life_sprite.w * 2.5  ;
    lives_start.h = life_sprite.h * 2.5  ;
    lives_start.x = constants::SCORE_BOARD_LIVES_START_X ;
    lives_start.y = constants::SCORE_BOARD_LIVES_START_Y;

    for (int i = 0 ; i < livesNb; i++){
        drawObject(render,texture, life_sprite, lives_start);
        lives_start.x += lives_start.w + 5  ;
    }
}

void ScoreBoard::updateFruits(const std::shared_ptr<SDL_Renderer> &render, const std::shared_ptr<SDL_Texture> &texture) {

    SDL_Rect position  ;
    position.x = constants::SCORE_BOARD_POINTS_START_X ;
    position.y = constants::SCORE_BOARD_POINTS_START_Y + 100;
    position.w = 24;
    position.h = 24 ;
    int offset = 24 + 5  ;

    for (SDL_Rect s : fruit_queue_ ){
        drawObject(render,texture,s,position);
        position.x += offset ;
    }
}

void ScoreBoard::addFruits(SDL_Rect fruit){
    if(fruit_queue_.size() == 5){
        fruit_queue_.pop_back() ;
    }
    fruit_queue_.insert(fruit_queue_.begin(), fruit);
}




