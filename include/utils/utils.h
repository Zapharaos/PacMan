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
#include <SDL.h>


template<typename T>
const T &getRandomElementFromSet(std::set<T> elements)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, elements.size() - 1);

    // Iterate through the set until we reach the element at the random index
    auto it = elements.begin();
    auto index = dis(gen);
    std::advance(it, index);

    // Extract the element at the random index
    return *it;
}

/**
 * @brief Returns the maximum number of objects of type T that can be stored.
 * @tparam T Object type.
 * @return Maximum number of T objects that can be stored.
 */
template<typename T>
constexpr int getMaximumLegalSize()
{
    return static_cast<int>(std::numeric_limits<std::size_t>::max() /
                            sizeof(T));
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
constexpr std::array<T, max> shrinkArray(const std::array<T, N> &array)
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


void saveGameState(unsigned long high_score, int round);


/**
 *getHighScore
 * get highest score reached locally
 * @return
 */
std::string getSavedHighScore();

/**
 * getRound
 * Get highest round reached locally from json file
 * @return round
 */
std::string getRound();


/**
 * drawObject
 * Draws a sprite ath the desired position
 * @param render
 * @param texture
 * @param src_rect Initial SDL_RECT
 * @param dst_rect Dest SDL_RECT
 */
void
drawObject(const std::shared_ptr<SDL_Renderer> &render, const std::shared_ptr<SDL_Texture> &texture, SDL_Rect src_rect,
           SDL_Rect dst_rect);


/**
 * saveGameState
 * Save local game state
 * @param high_score
 * @param round
 */
void saveGameState(unsigned long high_score, int round);
#endif //PACMAN_UTILS_H
