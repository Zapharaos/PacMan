//
// Created by omar on 01/03/23.
//

#ifndef PACMAN_WINDOW_H
#define PACMAN_WINDOW_H


#include <string>
#include <SDL.h>
#include "sprite/extractor.h"
#include <utility>
#include <memory>
#include "../include/game.h"


class Window {
private :
    int map_width_ ;
    int map_height_ ;
    int score_board_width_ ;

    SDL_Rect map_init_{} ;
    SDL_Rect map_empty_{} ;
    SDL_Rect map_white_{} ;

     SDL_Window* pWindow_ ;
     SDL_Surface* win_surf_ ;
     SDL_Surface* plancheSprites_ ;


     SDL_Rect src_bg_ ;
     SDL_Rect bg_ ;

    std::string title_ ;
public:
    Window(int mapWidth, int mapHeight, int scoreBoardWidth, const SDL_Rect &mapInit, const SDL_Rect &mapEmpty,
           const SDL_Rect &mapWhite, string title);

    [[nodiscard]] int getMapWidth() const;

    void setMapWidth(int mapWidth);

    [[nodiscard]] int getMapHeight() const;

    void setMapHeight(int mapHeight);

    [[nodiscard]] int getScoreBoardWidth() const;

    void setScoreBoardWidth(int scoreBoardWidth);

    [[nodiscard]] const std::string &getTitle() const;

    void setTitle(const std::string &title);

    [[nodiscard]] const SDL_Rect &getMapInit() const;

    void setMapInit(const SDL_Rect &mapInit);

    [[nodiscard]] const SDL_Rect &getMapEmpty() const;

    void setMapEmpty(const SDL_Rect &mapEmpty);

    [[nodiscard]] const SDL_Rect &getMapWhite() const;

    void setMapWhite(const SDL_Rect &mapWhite);
    //TODO create Window , get surface , get planche , draw function

     void createWindow();

    // fonction qui met à jour la surface de la fenetre "win_surf"
     void drawWindow();
};


#endif //PACMAN_WINDOW_H
