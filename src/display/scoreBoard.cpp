//
// Created by omar on 19/02/23.
//

#include "../../include/display/scoreBoard.h"


ScoreBoard::ScoreBoard() = default;

std::vector<SDL_Rect> ScoreBoard::getPointsToPrint(unsigned long points, const std::unordered_map<char,
        SDL_Rect> &character_map) {


    std::string c = std::to_string(points);
    std::vector<SDL_Rect> points_to_print;
    if(points == 0){
        points_to_print.push_back(character_map.at('0'));
        points_to_print.push_back(character_map.at('0'));

    }else{
        for (char i: c) {
            points_to_print.push_back(character_map.at(i));
        }
    }


    return points_to_print;
}

void ScoreBoard::writeLives(const std::shared_ptr<SDL_Renderer> &render,
                            const std::shared_ptr<SDL_Texture> &texture,
                            int livesNb) {
    SDL_Rect life_sprite = visuals::pacman::sprite_score_board::kSprite.getImage();
    SDL_Rect lives_start;
    lives_start.w = (int) (life_sprite.w * visuals::pacman::sprite_score_board::kScale);
    lives_start.h = (int) (life_sprite.h * visuals::pacman::sprite_score_board::kScale);
    lives_start.x = display::scoreboard::kScoreBoardLivesX;
    lives_start.y = display::scoreboard::kScoreBoardLivesY;

    for (int i = 0; i < livesNb; i++) {
        drawObject(render, texture, life_sprite, lives_start);
        lives_start.x += lives_start.w + 5;
    }
}

void
ScoreBoard::updateFruits(const std::shared_ptr<SDL_Renderer> &render, const std::shared_ptr<SDL_Texture> &texture) {

    SDL_Rect position;
    position.x = display::scoreboard::kScoreBoardFruitsX ;
    position.y = display::scoreboard::kScoreBoardFruitsY;
    position.w = visuals::fruit::cherry::sprite_1::kBitmapWidth * visuals::fruit::kScale;
    position.h = visuals::fruit::cherry::sprite_1::kBitmapHeight * visuals::fruit::kScale;
    int offset = position.w ;

    for (SDL_Rect s: fruit_queue_) {
        drawObject(render, texture, s, position);
        position.x -= offset;
    }
}

void ScoreBoard::addFruits(SDL_Rect fruit) {
    if (fruit_queue_.size() == 5) {
        fruit_queue_.pop_back();
    }
    fruit_queue_.insert(fruit_queue_.begin(), fruit);
}




