//
// Created by mfrei on 11/03/2023.
//

#include "../../include/utils/utils.h"

#include <fstream>

using json = nlohmann::json;
//TODO put map declaration in .h
std::unordered_map<int, SDL_Rect> sprite_map;

std::vector<CellType> loadCellTypesFromFile(const std::string &file_path)
{
    std::vector<CellType> cell_types;
    std::ifstream file; // indata is like cin
    char value; // variable for input value

    file.open(file_path); // opens the file
    if (!file)
    { // file couldn't be opened
        std::cerr << "Error: file could not be opened" << std::endl;
        exit(1);
    }
    file >> value;
    while (!file.eof())
    { // keep reading until end-of-file
        cell_types.emplace_back((CellType) strtol(&value, nullptr, 10));
        file >> value; // sets EOF flag if no value found
    }
    file.close();
    return cell_types;
}


/**
 * saveGameState
 * Save local game state
 * @param high_score
 * @param round
 */
void saveGameState(int high_score, int round) {

    json j =
            {
                    {"High Score",std::to_string(high_score)},
                    {"Round",std::to_string(round)}
            };

    // pretty print with indent of 4 spaces
    std::ofstream file("../resources/save.json");
    file << j ;
}
/**
 *getHighScore
 * get highest score ereached locally
 * @return
 */
std::string  getHighScore() {
    std::ifstream f("../resources/save.json");
    json data  = json::parse(f);
    std::string high_score = data.value("High Score","Not found");
    return high_score ;
}

/**
 * getRound
 * Get highest round reached locally from json
 * @return round
 */
std::string getRound() {
    std::ifstream f("../resources/save.json");
    json data  = json::parse(f);
    std::string round = data.value("Round","Not found");
    return round ;
}


/**
 * extractRowFromMap
 * extract a row of sprites from bitmap
 * @param width
 * @param height
 * @param number
 * @param start_x
 * @param start_y
 * @param offset
 * @return
 */
std::vector<SDL_Rect> extractRowFromMap(int width, int height, int number, int start_x,
                             int start_y, int offset) {
    //Vector to store sprites
    std::vector<SDL_Rect> tab ;
    for (int i = 0 ; i < number ; ++i ) {
        tab.push_back({start_x, start_y, width, height});
        start_x += width + offset; //skrrrr
    }
    return tab ;
}

/**
 * extractColumnFromMap
 * extract a column of sprites from a bitmap
 * @param width
 * @param height
 * @param number
 * @param start_x
 * @param start_y
 * @param offset
 * @return
 */
std::vector<SDL_Rect> extractColumnFromMap(int width, int height, int number, int start_x, int start_y, int offset) {
    //Vector to store sprites
    std::vector<SDL_Rect> tab ;
    for (int i = 0 ; i < number ; ++i ) {
        tab.push_back({start_x, start_y, width, height});
        start_y += height + offset; //skrrrr
    }
    return tab ;
}

/**
 *extractNthElementRowFromMap
 * To extract a singular sprite from a Row of sprites
 * @param width
 * @param height
 * @param number
 * @param start_x
 * @param start_y
 * @param offset
 * @return
 */
SDL_Rect extractNthElementRowFromMap(int width, int height, int number, int start_x, int start_y, int offset) {
    for (int i = 0 ; i < number ; ++i ) {
        start_x += width + offset; //skrrrr
    }
    SDL_Rect sprite = {start_x, start_y, width, height};
    return sprite ;
}


/**
 * extractNthElementColumnFromMap
 * To extract a singular sprite from a Column of sprites
 * @param width
 * @param height
 * @param number
 * @param start_x
 * @param start_y
 * @param offset
 * @return
 */
SDL_Rect extractNthElementColumnFromMap(int width, int height, int number, int start_x, int start_y, int offset) {
    for (int i = 0 ; i < number ; ++i ) {

        start_y += height + offset; //skrrrr
    }
    SDL_Rect sprite = {start_x, start_y, width, height};
    return sprite ;
}
/**
 * initPointSprites
 * Gets all point sprites from bitmap and stores them in hashmap
 */
void initPointSprites(){

    std::vector<SDL_Rect> points_rect ;
    //extract 200 to 800
    points_rect = extractColumnFromMap( constants::BMP_POINTS_WIDTH_THREE_CHARS,
                                        constants::BMP_POINTS_HEIGHT,
                                        3,
                                        constants::BMP_POINTS_START_ROW_1_X,
                                        constants::BMP_POINTS_START_ROW_1_Y,
                                        constants::BMP_POINTS_OFFSET
    );
    int x = 200 ;
    for(SDL_Rect i : points_rect){
        sprite_map.at(x) = i ;
        x = x * 2 ;
    }
    //100 to 700
    points_rect = extractColumnFromMap( constants::BMP_POINTS_WIDTH_THREE_CHARS,
                                        constants::BMP_POINTS_HEIGHT,
                                        4,
                                        constants::BMP_POINTS_START_ROW_2_X,
                                        constants::BMP_POINTS_START_ROW_2_Y,
                                        constants::BMP_POINTS_OFFSET
    );
    x = 100 ;
    for(SDL_Rect i : points_rect){
        sprite_map.at(x) = i ;
        x = x + 200  ;
    }

    sprite_map.at(1600) = {constants::BMP_POINTS_START_ROW_1_2_X,
                     constants::BMP_POINTS_START_ROW_1_2_Y,
                     constants::BMP_POINTS_WIDTH_FOUR_CHARS,
                     constants::BMP_POINTS_HEIGHT};


    //1000 to 5000
    points_rect = extractColumnFromMap( constants::BMP_POINTS_WIDTH_THREE_CHARS,
                                        constants::BMP_POINTS_HEIGHT,
                                        4,
                                        constants::BMP_POINTS_START_ROW_2_2_X,
                                        constants::BMP_POINTS_START_ROW_2_2_Y,
                                        constants::BMP_POINTS_OFFSET
    );

    x = 0 ;
    for(SDL_Rect i : points_rect){

        x = x + 1000  ;
        if(x==4000){
            sprite_map.at(5000) = i ;
        }else{
            sprite_map.at(x) = i ;
        }


    }
}
/**
 * Gets SDL_rect associated with points and converts it to a sprite.
 * @param points
 * @return
 */
Sprite getPointsSprite(int points){
    //Check if sprites have been set in map
    if(sprite_map.empty()){
        initPointSprites();
    }
    SDL_Rect rect  = sprite_map.at(points);

    return   Sprite(rect,
                    {constants::BMP_POINTS_SCALING_OFFSET,
                     constants::BMP_POINTS_SCALING_OFFSET},
                    {rect.w * 2 ,rect.h *2 });
}