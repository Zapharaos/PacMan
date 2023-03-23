//
// Created by mfrei on 11/03/2023.
//

#ifndef PACMAN_UTILS_H
#define PACMAN_UTILS_H

#include <utility>
#include <vector>
#include <array>
#include <unordered_map>
#include "json.hpp"
#include "../map/cell.h"
#include <SDL.h>

std::vector<CellType> loadCellTypesFromFile(const std::string &file_path);


void saveGameState(int high_score, int round);
std::string  getSavedHighScore();
std::string getRound();

std::vector <SDL_Rect> extractRowFromMap(int width, int height, int
number, int start_x, int start_y, int offset);

std::vector <SDL_Rect> extractColumnFromMap(int width, int height, int
number, int start_x, int start_y, int offset);

SDL_Rect extractNthElementRowFromMap(int width, int height, int number,
                                            int start_x, int start_y, int offset);

SDL_Rect extractNthElementColumnFromMap(int width, int height, int
number, int start_x, int start_y, int offset);

static Sprite getPointsSprite(int points);

void drawObject(const std::shared_ptr<SDL_Renderer>& render, const std::shared_ptr<SDL_Texture>& texture, SDL_Rect src_rect,
                SDL_Rect dst_rect);
#endif //PACMAN_UTILS_H
