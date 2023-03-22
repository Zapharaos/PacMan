//
// Created by omar on 01/03/23.
//

#include "../../include/display/window.h"

#include <utility>

Window::Window() = default;

Window::Window(int width, int height, std::string title) : width_(width), height_(height), title_(move(title)) {
    init();
}

void Window::init() {

    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }

    // triggers the program that controls graphics hardware and sets flags
    auto render_flags = SDL_RENDERER_ACCELERATED;

    window_ = std::shared_ptr<SDL_Window> (SDL_CreateWindow(&title_[0],
                                       SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                                       width_+ score_board_.getWidth(),
                                                       height_,
                                       SDL_WINDOW_SHOWN),SDL_DestroyWindow);

    renderer_ = std::shared_ptr<SDL_Renderer> (SDL_CreateRenderer(window_.get(), -1, render_flags), SDL_DestroyRenderer);

    texture_ = std::shared_ptr<SDL_Texture> (SDL_CreateTextureFromSurface(renderer_.get(), SDL_LoadBMP(constants::PATH_FILE_PACMAN_SPRITES)),
                                        SDL_DestroyTexture);
}

void Window::clear()
{
    SDL_QueryTexture(texture_.get(), nullptr, nullptr, &bg_.w, &bg_.h);
    SDL_RenderClear(renderer_.get());
}

void Window::update()
{
    SDL_RenderPresent(renderer_.get());
}

void Window::writeHighScore() {
    score_board_.writeHighScoreText(renderer_,texture_);
    //score_board_.writeHighScorePoints(renderer_,texture_,points);
}
void Window::updateHighScore(int points) {
    score_board_.writeHighScorePoints(renderer_,texture_,points);
}

void Window::updateScore(int score){
    score_board_.writeScorePoints(renderer_,texture_,score);
}

void Window::updateLives(int nb_lives){
    score_board_.writeLives(renderer_,texture_,nb_lives);
}

void Window::free(){
    SDL_DestroyRenderer(renderer_.get());
    SDL_DestroyWindow(window_.get());
    SDL_DestroyTexture(texture_.get());
}


void Window::updateFruits() {
    score_board_.updateFruits(renderer_,texture_);
}

void Window::addFruits(SDL_Rect fruit) {
    score_board_.addFruits(fruit);
}









