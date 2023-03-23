//
// Created by omar on 19/02/23.
//

#include "../../include/display/scoreBoard.h"

#include <utility>

ScoreBoard::ScoreBoard() = default;

ScoreBoard::ScoreBoard(int width, int height, std::vector<SDL_Rect> numbers) : width_(width), height_(height),
                                                                               numbers_(std::move(numbers)) {}



std::vector<SDL_Rect> ScoreBoard::getPointsToPrint(int points, const std::unordered_map<char,
        SDL_Rect> &character_map) {

    std::string c = std::to_string(points);
    std::vector<SDL_Rect> points_to_print;
    for (char i: c) {
        points_to_print.push_back(character_map.at(i));
    }
    return points_to_print;
}


int ScoreBoard::getWidth() const {
    return width_;
}




void ScoreBoard::writeLives(const std::shared_ptr<SDL_Renderer> &render,
                            const std::shared_ptr<SDL_Texture> &texture,
                            int livesNb) {
    SDL_Rect life_sprite = {
            constants::BMP_PACMAN_SCORE_BOARD_START_X,
            constants::BMP_PACMAN_SCORE_BOARD_START_Y,
            constants::BMP_PACMAN_SCORE_BOARD_WIDTH,
            constants::BMP_PACMAN_SCORE_BOARD_HEIGHT
    };
    SDL_Rect lives_start;
    lives_start.w = life_sprite.w * 2.5;
    lives_start.h = life_sprite.h * 2.5;
    lives_start.x = constants::SCORE_BOARD_LIVES_START_X;
    lives_start.y = constants::SCORE_BOARD_LIVES_START_Y;

    for (int i = 0; i < livesNb; i++) {
        drawObject(render, texture, life_sprite, lives_start);
        lives_start.x += lives_start.w + 5;
    }
}

void
ScoreBoard::updateFruits(const std::shared_ptr<SDL_Renderer> &render, const std::shared_ptr<SDL_Texture> &texture) {

    SDL_Rect position;
    position.x = constants::SCORE_BOARD_POINTS_START_X;
    position.y = constants::SCORE_BOARD_POINTS_START_Y + 100;
    position.w = 24;
    position.h = 24;
    int offset = 24 + 5;

    for (SDL_Rect s: fruit_queue_) {
        drawObject(render, texture, s, position);
        position.x += offset;
    }
}

void ScoreBoard::addFruits(SDL_Rect fruit) {
    if (fruit_queue_.size() == 5) {
        fruit_queue_.pop_back();
    }
    fruit_queue_.insert(fruit_queue_.begin(), fruit);
}




