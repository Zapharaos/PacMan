//
// Created by mfrei on 11/03/2023.
//

#ifndef PACMAN_UTILS_H
#define PACMAN_UTILS_H

#include <utility>
#include <vector>
#include "../map/cell.h"
#include "json.hpp"
#include <array>

vector<CellType> loadCellTypesFromFile(const string &file_path);

static void saveGameState(int high_score, int round);
static std::string  getHighScore();
static std::string getRound();

static std::vector <SDL_Rect> extractRowFromMap(int width, int height, int
number, int start_x, int start_y, int offset);

static std::vector <SDL_Rect> extractColumnFromMap(int width, int height, int
number, int start_x, int start_y, int offset);

static SDL_Rect extractNthElementRowFromMap(int width, int height, int number,
                                            int start_x, int start_y, int offset);

static SDL_Rect extractNthElementColumnFromMap(int width, int height, int
number, int start_x, int start_y, int offset);

#endif //PACMAN_UTILS_H
