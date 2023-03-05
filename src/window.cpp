//
// Created by omar on 01/03/23.
//



#include <utility>

#include "../include/window.h"




int Window::getMapWidth() const {
    return map_width_;
}

void Window::setMapWidth(int mapWidth) {
    map_width_ = mapWidth;
}

int Window::getMapHeight() const {
    return map_height_;
}

void Window::setMapHeight(int mapHeight) {
    map_height_ = mapHeight;
}

int Window::getScoreBoardWidth() const {
    return score_board_width_;
}

void Window::setScoreBoardWidth(int scoreBoardWidth) {
    score_board_width_ = scoreBoardWidth;
}

const std::string &Window::getTitle() const {
    return title_;
}

void Window::setTitle(const std::string &title) {
    title_ = title;
}

const SDL_Rect &Window::getMapInit() const {
    return map_init_;
}

void Window::setMapInit(const SDL_Rect &mapInit) {
    map_init_ = Extractor::extractNthElementRowFromMap(
            constants::MAP_WIDTH ,
            constants::MAP_HEIGHT,
            0,
            constants::BMP_MAP_START_X,
            constants::BMP_MAP_START_Y,
            1
            );
}

const SDL_Rect &Window::getMapEmpty() const {
    return map_empty_;
}

void Window::setMapEmpty(const SDL_Rect &mapEmpty) {
    map_empty_ = Extractor::extractNthElementRowFromMap(
            constants::MAP_WIDTH ,
            constants::MAP_HEIGHT,
            1,
            constants::BMP_MAP_START_X,
            constants::BMP_MAP_START_Y,
            1
    );
}

const SDL_Rect &Window::getMapWhite() const {
    return map_white_;
}

void Window::setMapWhite(const SDL_Rect &mapWhite) {
    map_white_ = Extractor::extractNthElementRowFromMap(
            constants::MAP_WIDTH ,
            constants::MAP_HEIGHT,
            2,
            constants::BMP_MAP_START_X,
            constants::BMP_MAP_START_Y,
            1
    );
}


Window::Window(int mapWidth, int mapHeight, int scoreBoardWidth, const SDL_Rect &mapInit, const SDL_Rect &mapEmpty,
               const SDL_Rect &mapWhite, string title) : map_width_(mapWidth), map_height_(mapHeight),
                                                                score_board_width_(scoreBoardWidth), map_init_(mapInit),
                                                                map_empty_(mapEmpty), map_white_(mapWhite),
                                                                title_(std::move(title)) {}

void Window::createWindow() {

    //auto pWindow = std::make_unique<SDL_Surface>  ;
    //auto win_surf = std::make_unique<SDL_Surface>  ;
    //auto plancheSprites = std::make_unique<SDL_Surface>  ;
    int count_;

    src_bg_ = { constants::BMP_MAP_START_X,constants::BMP_MAP_START_Y, constants::BMP_MAP_WIDTH,constants::BMP_MAP_HEIGHT }; // x,y, w,h (0,0) en haut a gauche
    bg_ = { constants::WINDOW_MAP_START_X,constants::WINDOW_MAP_START_Y, constants::WINDOW_MAP_WIDTH,constants::WINDOW_MAP_HEIGHT }; // ici scale x4

    //auto pWindow = std::make_unique<SDL_Surface> (SDL_CreateWindow("PacMan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, constants::WINDOW_MAP_WIDTH + constants::SCORE_BOARD_WIDTH ,constants::WINDOW_MAP_HEIGHT, SDL_WINDOW_SHOWN));

    pWindow_ = SDL_CreateWindow("PacMan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, constants::WINDOW_MAP_WIDTH + constants::SCORE_BOARD_WIDTH ,constants::WINDOW_MAP_HEIGHT, SDL_WINDOW_SHOWN);
    win_surf_ = SDL_GetWindowSurface(pWindow_);

    plancheSprites_ = SDL_LoadBMP(constants::PATH_FILE_PACMAN_SPRITES);
    Game* game = new Game(constants::MAP_WIDTH, constants::MAP_HEIGHT, constants::WINDOW_CELL_HEIGHT, constants::PATH_FILE_PACMAN_MAP, constants::LIVES);

}

void Window::drawWindow() {
    int count_ = 0;
    SDL_SetColorKey(plancheSprites_, false, 0);
    SDL_BlitScaled(plancheSprites_, &src_bg_, win_surf_, &bg_);

    // couleur transparente
    SDL_SetColorKey(plancheSprites_, true, 0);
}
