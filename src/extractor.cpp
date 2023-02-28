//
// Created by omar on 27/02/23.
//

#include <array>
#include "../include/extractor.h"


std::vector<SDL_Rect>
Extractor::extractRowFromMap(int width, int height, int number, int start_x,
                             int start_y, int offset) {
    //Vector to store sprites
    std::vector<SDL_Rect> tab ;
    for (int i = 0 ; i < number ; i++ ) {
         tab.push_back({start_x, start_y, width, height});
        start_x += offset; //skrrrr
    }
    return tab ;
}

std::vector<SDL_Rect>
Extractor::extractColumnFromMap(int width, int height, int number, int start_x, int start_y, int offset) {
    //Vector to store sprites
    std::vector<SDL_Rect> tab ;
    for (int i = 0 ; i < number ; i++ ) {
        tab.push_back({start_x, start_y, width, height});
        start_y += offset; //skrrrr
    }
    return tab ;
}
