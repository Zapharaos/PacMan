//
// Created by mfrei on 11/03/2023.
//

#include "../../include/utils/utils.h"

#include <fstream>

using json = nlohmann::json;

vector<CellType> loadCellTypesFromFile(const string &file_path)
{
    vector<CellType> cell_types;
    ifstream file; // indata is like cin
    char value; // variable for input value

    file.open(file_path); // opens the file
    if (!file)
    { // file couldn't be opened
        cerr << "Error: file could not be opened" << endl;
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
    for (int i = 0 ; i < number ; i++ ) {
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
    for (int i = 0 ; i < number ; i++ ) {
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
    for (int i = 0 ; i < number ; i++ ) {
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
    for (int i = 0 ; i < number ; i++ ) {

        start_y += height + offset; //skrrrr
    }
    SDL_Rect sprite = {start_x, start_y, width, height};
    return sprite ;
}

/**
 * drawObject
 * Draws desired sprite in a location
 * @param src
 * @param dst
 * @param src_rect
 * @param dst_rect
 *
 */
void drawObject( shared_ptr<SDL_Renderer> render
                 , shared_ptr<SDL_Texture> texture
                 , SDL_Rect src_rect
                 , SDL_Rect dst_rect  )
{
    SDL_RenderCopy(render.get(), texture.get(), &src_rect, &dst_rect);
    //SDL_RenderPresent(render.get());
}
