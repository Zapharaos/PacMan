//
// Created by omar on 01/03/23.
//




#include <utility>

#include "../../include/display/window.h"

/**
 * Window constructor
 * @param windowWidth
 * @param windowHeight
 * @param title
 */
Window::Window(int windowWidth, int windowHeight, string title) : window_width_(windowWidth),
                                                                         window_height_(windowHeight), title_(std::move(title)) {}



/**
 * createWindow
 * Creates a window and sets class members
 */
void Window::createWindow(shared_ptr<Game> game ) {

    game_ = std::move(game) ;
    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }

    // triggers the program that controls graphics hardware and sets flags
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;

    window_ = shared_ptr<SDL_Window> (SDL_CreateWindow("PacMan",
                                       SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                       window_width_+ scoreBoard_.getWidth(),
                                       window_height_,
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
/**
 * freeRessources
 * Free up allocated space
 */
void Window::freeRessources(){
    SDL_DestroyRenderer(render_.get());
    SDL_DestroyWindow(window_.get());
    SDL_DestroyTexture(texture_.get());
}
//TODO To cleanup
void Window::drawWindow(Direction last){

    StatusType statusType = game_->getStatus();
    if(statusType == StatusType::PAUSED) return; // nothing to update

    SDL_QueryTexture(texture_.get(), nullptr, nullptr, &bg_.w, &bg_.h);
    SDL_RenderClear(render_.get());

    SDL_Rect  map_ ;
    map_.w = 672 ;
    map_.h = 864 ;
    map_.x = 0 ;
    map_.y = 0 ;


    writeHighScore();
    updateHighScore(game_->getScore());
    drawObject(render_, texture_, map_default, map_);

    if(statusType == StatusType::INTERRUPTED)
    {
        // TODO : do animation + increase tick counter
        // TODO : after all animation ticks ended
        game_->setStatus(StatusType::RUNNING);
    }

    if(statusType == StatusType::LEVEL_UP) {
        if ((++mapTickCount) >= mapTickDelay) {
            mapTickCount = 0;
            mapSwitchCount++;
            if (mapSwitchCount == mapSwitchAmount) {
                mapSwitchCount = 0;
                last.reset(); // reset direction to stop the pacman from moving
                game_->levelUp();

                // TODO : temp ghost sprites reset
                ghost_blinky = {32, 32, constants::WINDOW_CELL_WIDTH, constants::WINDOW_CELL_HEIGHT};
                count_ = 0;
            }
        }
        if(mapSwitchCount%2 != 0)
            drawObject(render_,texture_, map_switch, map_);
    }

    if(statusType == StatusType::LOST_LIFE) {
        Pacman pacman = game_->getPacman();
        if (pacman.isDead()) {
            pacman.animateDeath(); // saved ?
            game_->setPacman(pacman);
            if (!pacman.isDead()) { // animation is over
                last.reset();
                game_->lostLife();
            }
        }
    }

    game_->drawStaticEntities(render_, texture_);
    // couleur transparente
    //SDL_SetColorKey(plancheSprites_, true, 0);
    //TODO Changer transparence avec SDL2

    Pacman pacman = game_->getPacman();
    SDL_Rect image = pacman.getSpriteImage();
    SDL_Rect position = pacman.getSpritePosition();
    drawObject(render_,texture_,image, position);

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
        drawObject(render_,texture_,ghost_in2, ghost_blinky);
    }
}

void Window::writeHighScore() {
    scoreBoard_.writeHighScoreText(render_,texture_);
    scoreBoard_.writeHighScorePoints(render_,texture_,game_->getHighScore());
}

void Window::updateHighScore(int points){
    if(game_->getScore()>game_->getHighScore()){
        scoreBoard_.writeHighScorePoints(render_,texture_,points);
    }
    scoreBoard_.writeScorePoints(render_,texture_,points);

}

const shared_ptr<SDL_Window> &Window::getWindow() const {
    return window_;
}

const shared_ptr<SDL_Renderer> &Window::getRender() const {
    return render_;
}

Window::~Window() = default;







