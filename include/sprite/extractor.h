//
// Created by omar on 27/02/23.
//

#ifndef PACMAN_EXTRACTOR_H
#define PACMAN_EXTRACTOR_H

#include <SDL_rect.h>
#include <vector>
#include "../utils/constants.h"

class Extractor {
public:
    static std::vector <SDL_Rect> extractRowFromMap(int width, int height, int
    number, int start_x, int start_y, int offset);

    static std::vector <SDL_Rect> extractColumnFromMap(int width, int height, int
    number, int start_x, int start_y, int offset);

    static SDL_Rect extractNthElementRowFromMap(int width, int height, int number,
                                                           int start_x, int start_y, int offset);

    static SDL_Rect extractNthElementColumnFromMap(int width, int height, int
    number, int start_x, int start_y, int offset);

};


#endif //PACMAN_EXTRACTOR_H
