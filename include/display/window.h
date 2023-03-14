//
// Created by omar on 01/03/23.
//

#ifndef PACMAN_WINDOW_H
#define PACMAN_WINDOW_H


#include <utility>
#include <memory>
#include "../game.h"
#include "scoreBoard.h"
#include "../utils/utils.h"

class Window {
private :

    // Width and height of the window
    int window_width_{} ;
    int window_height_{} ;

    //Main window
    std::shared_ptr<SDL_Window> window_ ;
    //Windw surface
    std::shared_ptr<SDL_Surface> win_surf_ ;
    //Sprite file
    std::shared_ptr<SDL_Surface> plancheSprites_ ;
    //renderer to render our images
    std::shared_ptr<SDL_Renderer> render_ ;
    //To load image t graphics hardware memory
    std::shared_ptr<SDL_Texture> texture_ ;
    //Window Title
    std::string title_ ;
    //ScoreBoard Object
    ScoreBoard scoreBoard_ {};

    std::shared_ptr<Game> game_ ;

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
    SDL_Rect bg_ = { constants::WINDOW_MAP_START_X,constants::WINDOW_MAP_START_Y, constants::WINDOW_MAP_WIDTH,constants::WINDOW_MAP_HEIGHT }; // ici scale x4

    SDL_Rect ghost_scared = { 3,195, constants::BMP_ENTITY_GHOST_WIDTH,constants::BMP_ENTITY_GHOST_HEIGHT };
    SDL_Rect ghost_blinky_r = { constants::BMP_GHOST_BLINKY_START_X + constants::BMP_ENTITY_GHOST_OFFSET_TO_RIGHT_IMG,constants::BMP_GHOST_BLINKY_START_Y, constants::BMP_ENTITY_GHOST_WIDTH,constants::BMP_ENTITY_GHOST_HEIGHT };
    SDL_Rect ghost_blinky_l = { constants::BMP_GHOST_BLINKY_START_X + constants::BMP_ENTITY_GHOST_OFFSET_TO_LEFT_IMG,constants::BMP_GHOST_BLINKY_START_Y, constants::BMP_ENTITY_GHOST_WIDTH,constants::BMP_ENTITY_GHOST_HEIGHT };
    SDL_Rect ghost_blinky_u = { constants::BMP_GHOST_BLINKY_START_X + constants::BMP_ENTITY_GHOST_OFFSET_TO_UP_IMG,constants::BMP_GHOST_BLINKY_START_Y, constants::BMP_ENTITY_GHOST_WIDTH,constants::BMP_ENTITY_GHOST_HEIGHT };
    SDL_Rect ghost_blinky_d = { constants::BMP_GHOST_BLINKY_START_X + constants::BMP_ENTITY_GHOST_OFFSET_TO_DOWN_IMG,constants::BMP_GHOST_BLINKY_START_Y, constants::BMP_ENTITY_GHOST_WIDTH,constants::BMP_ENTITY_GHOST_HEIGHT };
    SDL_Rect ghost_blinky = { 32,32, constants::WINDOW_CELL_WIDTH,constants::WINDOW_CELL_HEIGHT };     // ici scale x2

    Window(int windowWidth, int windowHeight, string title);

    void createWindow(shared_ptr<Game> game);

    // fonction qui met à jour la surface de la fenetre "win_surf"
    //void drawWindow(Game* game,Direction last);

    void writeHighScore();

    void updateHighScore(int points);


    [[nodiscard]] const shared_ptr<SDL_Window> &getWindow() const;


    void drawWindow(Direction last);

    void freeRessources();

    virtual ~Window();

    [[nodiscard]] const shared_ptr<SDL_Renderer> &getRender() const;

};


#endif //PACMAN_WINDOW_H
