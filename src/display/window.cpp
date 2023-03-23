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

    initSpriteMap();
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
    score_board_.writeHighScoreText(renderer_,texture_,character_map_);
}
void Window::updateHighScore(int points) {
    score_board_.writeHighScorePoints(renderer_,texture_,points,character_map_);
}

void Window::updateScore(int score){
    score_board_.writeScorePoints(renderer_,texture_,score,character_map_);
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

void Window::initSpriteMap(){
    /** Numbers */
    std::vector <SDL_Rect> numbers;
    numbers = extractRowFromMap( constants::BMP_CHARACTER_WIDTH,
                                  constants::BMP_CHARACTER_HEIGHT,
                                  9,
                                  constants::BMP_NUMBER_START_FIRST_ROW_X,
                                  constants::BMP_NUMBER_START_FIRST_ROW_Y,
                                  constants::OFFSET_CHAR
    );
    int i = 1 ;
    for(auto x : numbers){
        std::string c = std::to_string(i);

        printf("number is %d converted is %c \n",i, c[0]);
        character_map_.insert({c[0],x});
        i++ ;
    }
    //extract 0
    SDL_Rect sprite_zero = {constants::BMP_NUMBER_START_ZERO_ROW_X,
                            constants::BMP_NUMBER_START_FIRST_ROW_Y,
                            constants::BMP_CHARACTER_WIDTH,
                            constants::BMP_CHARACTER_HEIGHT};

    character_map_.insert({'0',sprite_zero});

    /** letters **/
    SDL_Rect letter ;
    //Get A
    letter = extractNthElementRowFromMap(
            constants::BMP_CHARACTER_WIDTH,
            constants::BMP_CHARACTER_HEIGHT,
            0,
            constants::BMP_NUMBER_START_SECOND_ROW_X,
            constants::BMP_NUMBER_START_SECOND_ROW_Y,
            constants::OFFSET_CHAR);
    character_map_.insert({'A',letter});
    //Get B
    letter = extractNthElementRowFromMap(
            constants::BMP_CHARACTER_WIDTH,
            constants::BMP_CHARACTER_HEIGHT,
            1,
            constants::BMP_NUMBER_START_SECOND_ROW_X,
            constants::BMP_NUMBER_START_SECOND_ROW_Y,
            constants::OFFSET_CHAR);
    character_map_.insert({'B',letter});
    //Get C
    letter  = extractNthElementRowFromMap(
            constants::BMP_CHARACTER_WIDTH,
            constants::BMP_CHARACTER_HEIGHT,
            2,
            constants::BMP_NUMBER_START_SECOND_ROW_X,
            constants::BMP_NUMBER_START_SECOND_ROW_Y,
            constants::OFFSET_CHAR);
    character_map_.insert({'C',letter});
    //Get D
    letter  = extractNthElementRowFromMap(
            constants::BMP_CHARACTER_WIDTH,
            constants::BMP_CHARACTER_HEIGHT,
            3,
            constants::BMP_NUMBER_START_SECOND_ROW_X,
            constants::BMP_NUMBER_START_SECOND_ROW_Y,
            constants::OFFSET_CHAR);
    character_map_.insert({'D',letter});
    //Get E
    letter  = extractNthElementRowFromMap(
            constants::BMP_CHARACTER_WIDTH,
            constants::BMP_CHARACTER_HEIGHT,
            4,
            constants::BMP_NUMBER_START_SECOND_ROW_X,
            constants::BMP_NUMBER_START_SECOND_ROW_Y,
            constants::OFFSET_CHAR);
    character_map_.insert({'E',letter});
    //Get F
    letter  = extractNthElementRowFromMap(
            constants::BMP_CHARACTER_WIDTH,
            constants::BMP_CHARACTER_HEIGHT,
            5,
            constants::BMP_NUMBER_START_SECOND_ROW_X,
            constants::BMP_NUMBER_START_SECOND_ROW_Y,
            constants::OFFSET_CHAR);
    character_map_.insert({'F',letter});
    //Get G
    letter = extractNthElementRowFromMap(
            constants::BMP_CHARACTER_WIDTH,
            constants::BMP_CHARACTER_HEIGHT,
            6,
            constants::BMP_NUMBER_START_SECOND_ROW_X,
            constants::BMP_NUMBER_START_SECOND_ROW_Y,
            constants::OFFSET_CHAR);
    character_map_.insert({'G',letter});
    //Get H
    letter = extractNthElementRowFromMap(
            constants::BMP_CHARACTER_WIDTH,
            constants::BMP_CHARACTER_HEIGHT,
            7,
            constants::BMP_NUMBER_START_SECOND_ROW_X,
            constants::BMP_NUMBER_START_SECOND_ROW_Y,
            constants::OFFSET_CHAR);
    character_map_.insert({'H',letter});
    //Get I
    letter  = extractNthElementRowFromMap(
            constants::BMP_CHARACTER_WIDTH,
            constants::BMP_CHARACTER_HEIGHT,
            8,
            constants::BMP_NUMBER_START_SECOND_ROW_X,
            constants::BMP_NUMBER_START_SECOND_ROW_Y,
            constants::OFFSET_CHAR);
    character_map_.insert({'I',letter});
    //Get j
    letter = extractNthElementRowFromMap(
            constants::BMP_CHARACTER_WIDTH,
            constants::BMP_CHARACTER_HEIGHT,
            9,
            constants::BMP_NUMBER_START_SECOND_ROW_X,
            constants::BMP_NUMBER_START_SECOND_ROW_Y,
            constants::OFFSET_CHAR);
    character_map_.insert({'J',letter});
    //Get K
    letter = extractNthElementRowFromMap(
            constants::BMP_CHARACTER_WIDTH,
            constants::BMP_CHARACTER_HEIGHT,
            10,
            constants::BMP_NUMBER_START_SECOND_ROW_X,
            constants::BMP_NUMBER_START_SECOND_ROW_Y,
            constants::OFFSET_CHAR);
    character_map_.insert({'K',letter});
    //Get L
    letter = extractNthElementRowFromMap(
            constants::BMP_CHARACTER_WIDTH,
            constants::BMP_CHARACTER_HEIGHT,
            11,
            constants::BMP_NUMBER_START_SECOND_ROW_X,
            constants::BMP_NUMBER_START_SECOND_ROW_Y,
            constants::OFFSET_CHAR);
    character_map_.insert({'L',letter});
    //Get M
    letter = extractNthElementRowFromMap(
            constants::BMP_CHARACTER_WIDTH,
            constants::BMP_CHARACTER_HEIGHT,
            12,
            constants::BMP_NUMBER_START_SECOND_ROW_X,
            constants::BMP_NUMBER_START_SECOND_ROW_Y,
            constants::OFFSET_CHAR);
    character_map_.insert({'M',letter});
    //Get N
    letter = extractNthElementRowFromMap(
            constants::BMP_CHARACTER_WIDTH,
            constants::BMP_CHARACTER_HEIGHT,
            13,
            constants::BMP_NUMBER_START_SECOND_ROW_X,
            constants::BMP_NUMBER_START_SECOND_ROW_Y,
            constants::OFFSET_CHAR);
    character_map_.insert({'N',letter});
    //Get O
    letter  = extractNthElementRowFromMap(
            constants::BMP_CHARACTER_WIDTH,
            constants::BMP_CHARACTER_HEIGHT,
            14,
            constants::BMP_NUMBER_START_SECOND_ROW_X,
            constants::BMP_NUMBER_START_SECOND_ROW_Y,
            constants::OFFSET_CHAR);
    character_map_.insert({'O',letter});
    //Get P
    letter  = extractNthElementRowFromMap(
            constants::BMP_CHARACTER_WIDTH,
            constants::BMP_CHARACTER_HEIGHT,
            0,
            constants::BMP_NUMBER_START_THIRD_ROW_X,
            constants::BMP_NUMBER_START_THIRD_ROW_Y,
            constants::OFFSET_CHAR);
    character_map_.insert({'P',letter});
    //Get P
    letter  = extractNthElementRowFromMap(
            constants::BMP_CHARACTER_WIDTH,
            constants::BMP_CHARACTER_HEIGHT,
            1,
            constants::BMP_NUMBER_START_THIRD_ROW_X,
            constants::BMP_NUMBER_START_THIRD_ROW_Y,
            constants::OFFSET_CHAR);
    character_map_.insert({'P',letter});
    //Get R
    letter  = extractNthElementRowFromMap(
            constants::BMP_CHARACTER_WIDTH,
            constants::BMP_CHARACTER_HEIGHT,
            2,
            constants::BMP_NUMBER_START_THIRD_ROW_X,
            constants::BMP_NUMBER_START_THIRD_ROW_Y,
            constants::OFFSET_CHAR);
    character_map_.insert({'R',letter});
    //Get S
    letter  = extractNthElementRowFromMap(
            constants::BMP_CHARACTER_WIDTH,
            constants::BMP_CHARACTER_HEIGHT,
            3,
            constants::BMP_NUMBER_START_THIRD_ROW_X,
            constants::BMP_NUMBER_START_THIRD_ROW_Y,
            constants::OFFSET_CHAR);
    character_map_.insert({'S',letter});
    //Get T
    letter  = extractNthElementRowFromMap(
            constants::BMP_CHARACTER_WIDTH,
            constants::BMP_CHARACTER_HEIGHT,
            4,
            constants::BMP_NUMBER_START_THIRD_ROW_X+1,
            constants::BMP_NUMBER_START_THIRD_ROW_Y+1,
            constants::OFFSET_CHAR);
    character_map_.insert({'T',letter});
    //Get U
    letter  = extractNthElementRowFromMap(
            constants::BMP_CHARACTER_WIDTH,
            constants::BMP_CHARACTER_HEIGHT,
            5,
            constants::BMP_NUMBER_START_THIRD_ROW_X+1,
            constants::BMP_NUMBER_START_THIRD_ROW_Y+1,
            constants::OFFSET_CHAR);
    character_map_.insert({'U',letter});
    //Get V
    letter  = extractNthElementRowFromMap(
            constants::BMP_CHARACTER_WIDTH,
            constants::BMP_CHARACTER_HEIGHT,
            6,
            constants::BMP_NUMBER_START_THIRD_ROW_X+1,
            constants::BMP_NUMBER_START_THIRD_ROW_Y+1,
            constants::OFFSET_CHAR);
    character_map_.insert({'V',letter});
    //Get W
    letter  = extractNthElementRowFromMap(
            constants::BMP_CHARACTER_WIDTH,
            constants::BMP_CHARACTER_HEIGHT,
            7,
            constants::BMP_NUMBER_START_THIRD_ROW_X+1,
            constants::BMP_NUMBER_START_THIRD_ROW_Y+1,
            constants::OFFSET_CHAR);
    character_map_.insert({'W',letter});
    //Get X
    letter  = extractNthElementRowFromMap(
            constants::BMP_CHARACTER_WIDTH,
            constants::BMP_CHARACTER_HEIGHT,
            8,
            constants::BMP_NUMBER_START_THIRD_ROW_X+1,
            constants::BMP_NUMBER_START_THIRD_ROW_Y+1,
            constants::OFFSET_CHAR);
    character_map_.insert({'X',letter});
    //Get Y
    letter  = extractNthElementRowFromMap(
            constants::BMP_CHARACTER_WIDTH,
            constants::BMP_CHARACTER_HEIGHT,
            9,
            constants::BMP_NUMBER_START_THIRD_ROW_X+1,
            constants::BMP_NUMBER_START_THIRD_ROW_Y+1,
            constants::OFFSET_CHAR);
    character_map_.insert({'Y',letter});
    //Get Z
    letter  = extractNthElementRowFromMap(
            constants::BMP_CHARACTER_WIDTH,
            constants::BMP_CHARACTER_HEIGHT,
            10,
            constants::BMP_NUMBER_START_THIRD_ROW_X+1,
            constants::BMP_NUMBER_START_THIRD_ROW_Y+1,
            constants::OFFSET_CHAR);
    character_map_.insert({'Z',letter});
    /** Extra Characters */
    //Get .
   letter  = extractNthElementRowFromMap(
            2,
            2,
            11,
            constants::BMP_NUMBER_START_THIRD_ROW_X+1,
            constants::BMP_NUMBER_START_THIRD_ROW_Y+1,
            constants::OFFSET_CHAR);
    character_map_.insert({'.',letter});
    // Get /
    letter = {93,54,5,5};
    character_map_.insert({'/',letter});
    // Get '
    letter = {125,69,5,4};
    character_map_.insert({'\'',letter});
    // Get corporation logo C saved in map as `
    letter = {116,69,8,8};
    character_map_.insert({'`',letter});
}









