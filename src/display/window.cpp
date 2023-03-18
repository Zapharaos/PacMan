//
// Created by omar on 01/03/23.
//

#include <utility>

#include "../../include/display/window.h"

Window::Window() = default;

Window::Window(int width, int height, string title) : width_(width), height_(height), title_(move(title)) {
    init();
}

void Window::init() {

    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }

    // triggers the program that controls graphics hardware and sets flags
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;

    window_ = shared_ptr<SDL_Window> (SDL_CreateWindow(&title_[0],
                                       SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                                       width_+ scoreBoard_.getWidth(),
                                                       height_,
                                       SDL_WINDOW_SHOWN),SDL_DestroyWindow);

    win_surf_ = shared_ptr<SDL_Surface> (SDL_GetWindowSurface(window_.get()));

    plancheSprites_ = shared_ptr<SDL_Surface> (SDL_LoadBMP(constants::PATH_FILE_PACMAN_SPRITES));

    render_ = shared_ptr<SDL_Renderer> (SDL_CreateRenderer(window_.get(), -1, render_flags), SDL_DestroyRenderer);

    texture_ = shared_ptr<SDL_Texture> (SDL_CreateTextureFromSurface(render_.get(),plancheSprites_.get()),
                                        SDL_DestroyTexture);

    //SDL_FreeSurface(plancheSprites_.get());

    // connects our texture with dest to control position
    SDL_QueryTexture(texture_.get(), nullptr, nullptr, &bg_.w, &bg_.h);

    SDL_RenderClear(render_.get());
}

void Window::clear()
{
    SDL_QueryTexture(texture_.get(), nullptr, nullptr, &bg_.w, &bg_.h);
    SDL_RenderClear(render_.get());
}

void Window::update()
{
    SDL_RenderPresent(render_.get());
}

void Window::writeHighScore() {
    /*scoreBoard_.writeHighScoreText(render_,texture_);
    scoreBoard_.writeHighScorePoints(render_,texture_,game_->getHighScore());*/
}

void Window::updateHighScore(int points){
    /*if(game_->getScore()>game_->getHighScore()){
        scoreBoard_.writeHighScorePoints(render_,texture_,points);
    }
    scoreBoard_.writeScorePoints(render_,texture_,points);*/
}

void Window::free(){
    SDL_DestroyRenderer(render_.get());
    SDL_DestroyWindow(window_.get());
    SDL_DestroyTexture(texture_.get());
}







