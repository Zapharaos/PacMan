//
// Created by omar on 01/03/23.
//




#include <utility>

#include "../../include/display/window.h"



const SDL_Rect &Window::getMapInit() {
    return map_init_;
}

void Window::setMapInit(const SDL_Rect &mapInit) {
    map_init_ = Extractor::extractNthElementRowFromMap(
            constants::MAP_WIDTH ,
            constants::MAP_HEIGHT,
            0,
            constants::BMP_MAP_START_X,
            constants::BMP_MAP_START_Y,
            constants::OFFSET_MAP
    );
}

const SDL_Rect &Window::getMapEmpty() {
    return map_empty_;
}

void Window::setMapEmpty(const SDL_Rect &mapEmpty) {
    map_empty_ = Extractor::extractNthElementRowFromMap(
            constants::MAP_WIDTH ,
            constants::MAP_HEIGHT,
            1,
            constants::BMP_MAP_START_X,
            constants::BMP_MAP_START_Y,
            constants::OFFSET_MAP
    );
}

const SDL_Rect &Window::getMapWhite() {
    return map_white_;
}

void Window::setMapWhite(const SDL_Rect &mapWhite) {
    map_white_ = Extractor::extractNthElementRowFromMap(
            constants::MAP_WIDTH ,
            constants::MAP_HEIGHT,
            2,
            constants::BMP_MAP_START_X,
            constants::BMP_MAP_START_Y,
            constants::OFFSET_MAP
    );
}



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

    scoreBoard_.setHighScore(scoreBoard_.getSavedHighScore());
    writeHighScore();

}

void Window::drawWindow(Game* game, Direction last) {

    StatusType statusType = game->getStatus();
    if(statusType == StatusType::PAUSED) return; // nothing to update

    SDL_SetColorKey(plancheSprites_, false, 0);
    SDL_BlitScaled(plancheSprites_, &map_default, win_surf_, &bg_);

    if((++energizerTickCount) >= energizerTickDelay*2)
        energizerTickCount = 0;

    if(statusType == StatusType::INTERRUPTED)
    {
        // TODO : do animation + increase tick counter
        // TODO : after all animation ticks ended
        game->setStatus(StatusType::RUNNING);
    }

    if(statusType == StatusType::LEVEL_UP)
    {
        if((++mapTickCount) >= mapTickDelay) {
            mapTickCount = 0;
            mapSwitchCount++;
            if(mapSwitchCount == mapSwitchAmount)
            {
                mapSwitchCount = 0;
                last.reset(); // reset direction to stop the pacman from moving
                game->levelUp();

                // TODO : temp ghost sprites reset
                ghost_blinky = { 32,32, constants::WINDOW_CELL_WIDTH,constants::WINDOW_CELL_HEIGHT };
                count_ = 0;
            }
        }
        if(mapSwitchCount%2 != 0)
            SDL_BlitScaled(plancheSprites_, &map_switch, win_surf_, &bg_);
    }

    if(statusType == StatusType::LOST_LIFE) {
        Pacman pacman = game->getPacman();
        if(pacman.isDead() && (++deathTickCount) == deathTickDelay) {
            deathTickCount = 0;
            pacman.animateDeath(); // saved ?
            game->setPacman(pacman);
            if(!pacman.isDead()) { // animation is over
                last.reset();
                game->lostLife();
            }
        }
    }

    game->drawStaticEntities(plancheSprites_, win_surf_, energizerTickCount >= energizerTickDelay);

    // couleur transparente
    SDL_SetColorKey(plancheSprites_, true, 0);

    // display pacman
    Pacman pacman = game->getPacman();
    SDL_Rect image = pacman.getSpriteImage();
    SDL_Rect position = pacman.getSpritePosition();
    SDL_BlitScaled(plancheSprites_, &image, win_surf_, &position);

    // TODO : display ghosts => this is only temporary
    if(statusType == StatusType::RUNNING)
    {
        // petit truc pour faire tourner le fantome
        SDL_Rect* ghost_in = nullptr;
        switch (count_ / 128)
        {
            case 0:
                ghost_in = &(ghost_blinky_r);
                ghost_blinky.x+=constants::GHOST_SPEED;
                break;
            case 1:
                ghost_in = &(ghost_blinky_d);
                ghost_blinky.y+=constants::GHOST_SPEED;
                break;
            case 2:
                ghost_in = &(ghost_blinky_l);
                ghost_blinky.x-=constants::GHOST_SPEED;
                break;
            case 3:
                ghost_in = &(ghost_blinky_u);
                ghost_blinky.y-=constants::GHOST_SPEED;
                break;
        }
        count_ = (count_ + 1) % (512);

        if(pacman.isSuperpower())
        {
            // TODO : ghost scared
            ghost_in = &(ghost_scared);
        }

        // ici on change entre les 2 sprites sources pour une jolie animation.
        SDL_Rect ghost_in2 = *ghost_in;
        if ((count_ / 4) % 2)
            ghost_in2.x += constants::BMP_ENTITY_GHOST_TOTAL_WIDTH;

        // copie du sprite zoomé
        SDL_BlitScaled(plancheSprites_, &ghost_in2, win_surf_, &ghost_blinky);
    }

    updateHighScore(game->getScore());
}

void Window::writeHighScore() {
    scoreBoard_.writeHighScoreText(win_surf_,plancheSprites_);
    scoreBoard_.writeHighScorePoints(win_surf_,plancheSprites_,scoreBoard_.getHighScore());
}

void Window::updateHighScore(int points){
    if(scoreBoard_.getScore()>scoreBoard_.getHighScore()){
        scoreBoard_.writeHighScorePoints(win_surf_,plancheSprites_,points);
    }
    scoreBoard_.writeScorePoints(win_surf_,plancheSprites_,points);

}

SDL_Window *Window::getPWindow() const {
    return pWindow_;
}

void Window::setPWindow(SDL_Window *pWindow) {
    pWindow_ = pWindow;
}

void  Window::spriteRender(SDL_Rect src, SDL_Rect dest, bool flag, SDL_Surface planche, SDL_Surface win_surface, int key) {
    SDL_SetColorKey (&planche,flag,key);
    SDL_BlitScaled(&planche,
                   &src,
                   &win_surface,
                   &dest
    );
}

Window::Window(string title) : title_(std::move(title)) {}






