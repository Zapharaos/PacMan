//
// Created by omar on 01/03/23.
//

#ifndef PACMAN_WINDOW_H
#define PACMAN_WINDOW_H


//#include <string>
#//include <SDL.h>
//#include "../sprite/extractor.h"
#include <utility>
#include <memory>
#include "../game.h"
#include "scoreBoard.h"
//#include <utility>


class Window {
private :
    int map_width_ ;
    int map_height_ ;
    int score_board_width_ ;

    SDL_Rect map_init_ ;
    SDL_Rect map_empty_ ;
    SDL_Rect map_white_ ;

    SDL_Window* pWindow_ ;
    SDL_Surface* win_surf_ ;
    SDL_Surface* plancheSprites_ ;
    SDL_Rect src_bg_ ;
    SDL_Rect bg_ ;

    std::string title_ ;

    ScoreBoard scoreBoard_ {};
    //Game game_{};

public:

    int count_ = 0;
    int deathTickDelay = 7;
    int deathTickCount = 0;

    int energizerTickDelay = 30;
    int energizerTickCount = 0;

    int mapSwitchAmount = 14;
    int mapSwitchCount = 0;
    int mapTickDelay = 15;
    int mapTickCount = 0;

    SDL_Rect map_default = { constants::BMP_MAP_START_X,constants::BMP_MAP_START_Y, constants::BMP_MAP_WIDTH,constants::BMP_MAP_HEIGHT }; // x,y, w,h (0,0) en haut a gauche
    SDL_Rect map_switch = { 540,constants::BMP_MAP_START_Y, constants::BMP_MAP_WIDTH,constants::BMP_MAP_HEIGHT }; // x,y, w,h (0,0) en haut a gauche

    SDL_Rect ghost_scared = { 3,195, constants::BMP_ENTITY_GHOST_WIDTH,constants::BMP_ENTITY_GHOST_HEIGHT };
    SDL_Rect ghost_blinky_r = { constants::BMP_GHOST_BLINKY_START_X + constants::BMP_ENTITY_GHOST_OFFSET_TO_RIGHT_IMG,constants::BMP_GHOST_BLINKY_START_Y, constants::BMP_ENTITY_GHOST_WIDTH,constants::BMP_ENTITY_GHOST_HEIGHT };
    SDL_Rect ghost_blinky_l = { constants::BMP_GHOST_BLINKY_START_X + constants::BMP_ENTITY_GHOST_OFFSET_TO_LEFT_IMG,constants::BMP_GHOST_BLINKY_START_Y, constants::BMP_ENTITY_GHOST_WIDTH,constants::BMP_ENTITY_GHOST_HEIGHT };
    SDL_Rect ghost_blinky_u = { constants::BMP_GHOST_BLINKY_START_X + constants::BMP_ENTITY_GHOST_OFFSET_TO_UP_IMG,constants::BMP_GHOST_BLINKY_START_Y, constants::BMP_ENTITY_GHOST_WIDTH,constants::BMP_ENTITY_GHOST_HEIGHT };
    SDL_Rect ghost_blinky_d = { constants::BMP_GHOST_BLINKY_START_X + constants::BMP_ENTITY_GHOST_OFFSET_TO_DOWN_IMG,constants::BMP_GHOST_BLINKY_START_Y, constants::BMP_ENTITY_GHOST_WIDTH,constants::BMP_ENTITY_GHOST_HEIGHT };
    SDL_Rect ghost_blinky = { 32,32, constants::WINDOW_CELL_WIDTH,constants::WINDOW_CELL_HEIGHT };     // ici scale x2

    explicit Window(string title);

    [[nodiscard]]  const SDL_Rect &getMapInit() ;

    void setMapInit(const SDL_Rect &mapInit);

    [[nodiscard]] const SDL_Rect &getMapEmpty() ;

    void setMapEmpty(const SDL_Rect &mapEmpty);

    [[nodiscard]]  const SDL_Rect &getMapWhite() ;

    void setMapWhite(const SDL_Rect &mapWhite);

    [[nodiscard]] SDL_Window *getPWindow() const;

    void setPWindow(SDL_Window *pWindow);

    void static spriteRender(SDL_Rect src, SDL_Rect dest, bool flag, SDL_Surface planche, SDL_Surface win_surface, int key);

    void createWindow();

    // fonction qui met à jour la surface de la fenetre "win_surf"
    void drawWindow(Game* game,Direction last);

    void writeHighScore();

    void updateHighScore(int points);
};


#endif //PACMAN_WINDOW_H
