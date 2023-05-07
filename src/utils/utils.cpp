/**
 * @file utils.cpp
 * @brief Implementation of various utility functions for the Pac-Man game.
 */

#include "../../include/utils/utils.h"

#include <fstream>

using json = nlohmann::json;

std::vector<CellType> loadCellTypesFromFile(const std::string &file_path)
{
    std::vector<CellType> cell_types;

    std::ifstream file(file_path);
    if (!file)
    { // file couldn't be opened
        std::cerr << "Error: file could not be opened" << std::endl;
        exit(1);
    }

    int value;
    while (file >> value)
    { // Loop through each integer in the file
        cell_types.emplace_back((CellType) value);
    }

    file.close();
    return cell_types;
}



void saveGameState(unsigned long high_score, int round)
{
    json j =
            {
                    {"High Score", std::to_string(high_score)},
                    {"Round",      std::to_string(round)}
            };



    // Open the file for writing
    std::ofstream file("../resources/save.json");
    if (!file) {
        std::cerr << "Failed to open file for writing!\n";
        return;
    }
    // Pretty print with indent of 4 spaces
    file << j ;
}


std::string getSavedHighScore()
{

    // Check if the file exists
    std::ifstream infile("../resources/save.json");
    bool file_exists = infile.good();
    std::string high_score = "0";

    // If the file does not exist, create it
    if (!file_exists) {
        std::ofstream file("../resources/save.json", std::ofstream::out);
        if (!file) {
            std::cerr << "Failed to create file!\n";
        }
        return high_score ;
    }
    std::ifstream f("../resources/save.json");
    json data = json::parse(f);
    high_score = data.value("High Score", "0");
    return high_score;
}


std::string getRound()
{
    std::ifstream f("../resources/save.json");
    json data = json::parse(f);
    std::string round = data.value("Round", "Not found");
    return round;
}



void
drawObject(const std::shared_ptr<SDL_Renderer> &render, const std::shared_ptr<SDL_Texture> &texture, SDL_Rect src_rect,
           SDL_Rect dst_rect ) {
    SDL_RenderCopy(render.get(), texture.get(), &src_rect, &dst_rect);
}