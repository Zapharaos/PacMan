/**
 * @file utils.h
 * @brief Defines various utility functions for the Pac-Man game.
 */

#ifndef PACMAN_UTILS_H
#define PACMAN_UTILS_H

#include <utility>
#include <vector>
#include <array>
#include <unordered_map>
#include "json.hpp"
#include "../map/cell.h"
#include "../config/config.h"
#include "../config/constants.h"
#include <SDL.h>

/**
 * @brief Returns the maximum number of objects of type T that can be stored.
 * @tparam T Object type.
 * @return Maximum number of T objects that can be stored.
 */
template<typename T>
constexpr int getMaximumLegalSize() {
    return static_cast<int>(std::numeric_limits<std::size_t>::max() / sizeof(T));
}

/**
 * @brief Shrinks an array to a smaller size.
 * @tparam T Object type stored within the array.
 * @tparam max Size to shrink to.
 * @tparam N Current size of the array.
 * @param array The original array.
 * @return The resized array.
 */
template<typename T, std::size_t max, std::size_t N>
constexpr std::array<T, max> shrinkArray(const std::array<T, N>& array)
{
    std::array<T, max> resized;
    std::copy(array.begin(), array.begin() + max, resized.begin());
    return resized;
}

/**
 * @brief Loads the map settings from a file.
 * @param file_path Path to the file.
 * @return List of cells representing the map.
 */
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
