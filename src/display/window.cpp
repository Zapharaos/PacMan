//
// Created by omar on 01/03/23.
//

#include "../../include/display/window.h"
#include "../../include/entity/movingEntity.h"

Window::Window() = default;

void Window::init() {

    width_ = config::dimensions::kWindowWidth;
    height_ = config::dimensions::kWindowHeight;
    title_ = config::settings::kName;

    initSpriteMap();

    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }

    // triggers the program that controls graphics hardware and sets flags
    auto render_flags = SDL_RENDERER_ACCELERATED;

    window_ = std::shared_ptr<SDL_Window>(SDL_CreateWindow(&title_[0],
                                                           SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                                           width_ ,
                                                           height_,
                                                           SDL_WINDOW_SHOWN), SDL_DestroyWindow);

    renderer_ = std::shared_ptr<SDL_Renderer>(SDL_CreateRenderer(window_.get(), -1, render_flags), SDL_DestroyRenderer);
    surface_ = std::shared_ptr<SDL_Surface>(SDL_LoadBMP((config::files::kBitmap) ));
    Uint32 black = SDL_MapRGB(surface_->format, 0, 0, 0); // Get the pixel value for black
    SDL_SetColorKey(surface_.get(), SDL_TRUE, black); // Set black as the transparent color

    texture_ = std::shared_ptr<SDL_Texture> (SDL_CreateTextureFromSurface(renderer_.get(), surface_.get()),
                                        SDL_DestroyTexture);
    // Set the blend mode to blend the texture with the background
    SDL_SetTextureBlendMode(texture_.get(), SDL_BLENDMODE_BLEND);
}

void Window::clear() {
    SDL_QueryTexture(texture_.get(), nullptr, nullptr, &width_, &height_);
    SDL_RenderClear(renderer_.get());
}

void Window::update() {
    SDL_RenderPresent(renderer_.get());
}

void Window::writeHighScore() {
    //TODO make 1up flash
    writeWord("1UP",
              display::scoreboard::kScoreBoardOneUpTextX ,
              display::scoreboard::kScoreBoardOneUpTextY ,
              2,visuals::kScaleCell);

    writeWord("HIGH SCORE ",
              display::scoreboard::kScoreBoardHighScoreTextX ,
              display::scoreboard::kScoreBoardHighScoreTextY ,
            2,visuals::kScaleCell);
}

void Window::updateHighScore(unsigned long points) {
    writeScorePoints(points, display::scoreboard::kScoreBoardHighScoreX,
                     display::scoreboard::kScoreBoardHighScoreY, scales::kScore);
}

void Window::updateScore(unsigned long score) {
    writeScorePoints(score,
                     display::scoreboard::kScoreBoardScoreX,
                     display::scoreboard::kScoreBoardScoreY, scales::kScore);
}

void Window::updateLives(int nb_lives) {
    ScoreBoard::writeLives(renderer_, texture_, nb_lives);
}

void Window::updateFruits() {
    score_board_.updateFruits(renderer_, texture_);
}

void Window::addFruits(SDL_Rect fruit) {
    score_board_.addFruits(fruit);
}

void Window::initSpriteMap() {
    /** Numbers */
    character_map_.insert({'1', characters::numbers::one::kSprite.getImage()});
    character_map_.insert({'2', characters::numbers::two::kSprite.getImage()});
    character_map_.insert({'3', characters::numbers::three::kSprite.getImage()});
    character_map_.insert({'4', characters::numbers::four::kSprite.getImage()});
    character_map_.insert({'5', characters::numbers::five::kSprite.getImage()});
    character_map_.insert({'6', characters::numbers::six::kSprite.getImage()});
    character_map_.insert({'7', characters::numbers::seven::kSprite.getImage()});
    character_map_.insert({'8', characters::numbers::eight::kSprite.getImage()});
    character_map_.insert({'9', characters::numbers::nine::kSprite.getImage()});
    character_map_.insert({'0', characters::numbers::zero::kSprite.getImage()});

    /** letters **/
    //Get A
    character_map_.insert({'A',characters::letters::a::kSprite.getImage() });
    //Get B
    character_map_.insert({'B', characters::letters::b::kSprite.getImage()});
    //Get C
    character_map_.insert({'C', characters::letters::c::kSprite.getImage()});
    //Get D
    character_map_.insert({'D', characters::letters::d::kSprite.getImage()});
    //Get E
    character_map_.insert({'E', characters::letters::e::kSprite.getImage()});
    //Get F
    character_map_.insert({'F', characters::letters::f::kSprite.getImage()});
    //Get G
    character_map_.insert({'G', characters::letters::g::kSprite.getImage()});
    //Get H
    character_map_.insert({'H', characters::letters::h::kSprite.getImage()});
    //Get I
    character_map_.insert({'I', characters::letters::i::kSprite.getImage()});
    //Get j
    character_map_.insert({'J', characters::letters::j::kSprite.getImage()});
    //Get K
    character_map_.insert({'K', characters::letters::k::kSprite.getImage()});
    //Get L
    character_map_.insert({'L', characters::letters::l::kSprite.getImage()});
    //Get M
    character_map_.insert({'M', characters::letters::m::kSprite.getImage()});
    //Get N
    character_map_.insert({'N', characters::letters::n::kSprite.getImage()});
    //Get O
    character_map_.insert({'O', characters::letters::o::kSprite.getImage()});
    //Get P
    character_map_.insert({'P', characters::letters::p::kSprite.getImage()});
    //Get Q
    character_map_.insert({'Q', characters::letters::q::kSprite.getImage()});
    //Get R
    character_map_.insert({'R', characters::letters::r::kSprite.getImage()});
    //Get S
    character_map_.insert({'S', characters::letters::s::kSprite.getImage()});
    //Get T
    character_map_.insert({'T', characters::letters::t::kSprite.getImage()});
    //Get U
    character_map_.insert({'U', characters::letters::u::kSprite.getImage()});
    //Get V
    character_map_.insert({'V', characters::letters::v::kSprite.getImage()});
    //Get W
    character_map_.insert({'W', characters::letters::w::kSprite.getImage()});
    //Get X
    character_map_.insert({'X', characters::letters::x::kSprite.getImage()});
    //Get Y
    character_map_.insert({'Y', characters::letters::y::kSprite.getImage()});
    //Get Z
    character_map_.insert({'Z', characters::letters::z::kSprite.getImage()});
    /** Extra Characters */
    //Get .
    character_map_.insert({'.', characters::special::dot::kSprite.getImage()});
    // Get /
    character_map_.insert({'/', characters::special::slash::kSprite.getImage()});
    // Get '
    character_map_.insert({'\'', characters::special::apostrophe::kSprite.getImage()});
    // Get corporation logo C saved in map as `
    character_map_.insert({'`', characters::special::corp::kSprite.getImage()});
    // Get -
    character_map_.insert({'-', characters::special::dash::kSprite.getImage()});
    // Get !
    character_map_.insert({'!', characters::special::exclamation::kSprite.getImage()});


    /** init points map*/
    points_map_.insert({100,characters::points::points_100::kSprite.getImage()});
    points_map_.insert({200,characters::points::points_200::kSprite.getImage()});
    points_map_.insert({300,characters::points::points_300::kSprite.getImage()});
    points_map_.insert({400,characters::points::points_400::kSprite.getImage()});
    points_map_.insert({500,characters::points::points_500::kSprite.getImage()});
    points_map_.insert({700,characters::points::points_700::kSprite.getImage()});
    points_map_.insert({800,characters::points::points_800::kSprite.getImage()});
    points_map_.insert({1000,characters::points::points_1000::kSprite.getImage()});
    points_map_.insert({1600,characters::points::points_1600::kSprite.getImage()});
    points_map_.insert({2000,characters::points::points_2000::kSprite.getImage()});
    points_map_.insert({3000,characters::points::points_3000::kSprite.getImage()});
    points_map_.insert({5000,characters::points::points_5000::kSprite.getImage()});


}

int Window::centerImage(SDL_Rect src,int x){
    return (x-src.w/2);
}


void Window::writeScorePoints(unsigned long points, int pos_x, int pos_y, float scale, std::tuple<int, int, int> colour) {

    std::vector<SDL_Rect> points_to_print = ScoreBoard::getPointsToPrint(points, character_map_);
    SDL_Rect position = points_to_print[0];

    position.y = pos_y;
    position.w = (int )( characters::numbers::kBitmapWidth * scale);
    position.h = (int ) (characters::numbers::kBitmapWidth * scale);
    position.x = centerImage(position ,pos_x );

    if (colour!=colours::kWhite){
        SDL_SetTextureColorMod(texture_.get(),
                               std::get<0>(colour),
                               std::get<1>(colour),
                               std::get<2>(colour));
    }

    int offset = position.w;
    for (SDL_Rect s: points_to_print) {
        drawObject(renderer_, texture_, s, position);
        position.x += offset + 5  ;
    }
    if (colour!=colours::kWhite){
        SDL_SetTextureColorMod(texture_.get(),
                               std::get<0>(colours::kWhite),
                               std::get<1>(colours::kWhite),
                               std::get<2>(colours::kWhite));
    }
}

void Window::writeWord(const std::string &word, int pos_x, int pos_y, int offset, float scale , std::tuple<int, int, int> colour) {
    SDL_Rect dest;
    dest.x = pos_x;
    dest.y = pos_y;

    if (colour!=colours::kWhite){
        SDL_SetTextureColorMod(texture_.get(),
                               std::get<0>(colour),
                               std::get<1>(colour),
                               std::get<2>(colour));
    }
    for (char c: word) {
        if(!std::isspace(c)){
            SDL_Rect src = character_map_.at(c) ;
            dest.w = (int)( (float)src.w * scale  );
            dest.h = (int)( (float)src.h * scale  );
            drawObject(renderer_, texture_,
                       character_map_.at(c),
                       dest);
            dest.x += dest.w + offset;
        }else{
            dest.x += dest.w + offset;
        }

    }
    if (colour!=colours::kWhite){
        SDL_SetTextureColorMod(texture_.get(),
                               std::get<0>(colours::kWhite),
                               std::get<1>(colours::kWhite),
                               std::get<2>(colours::kWhite));
    }

}

const std::shared_ptr<SDL_Renderer> &Window::getRenderer() const {
    return renderer_;
}

const std::shared_ptr<SDL_Texture> &Window::getTexture() const {
    return texture_;
}

const std::unordered_map<unsigned long, SDL_Rect> &Window::getPointsMap() const {
    return points_map_;
}

void Window::quit()
{
    SDL_Quit();
}
