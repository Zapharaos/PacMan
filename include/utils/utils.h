//
// Created by mfrei on 11/03/2023.
//

#ifndef PACMAN_UTILS_H
#define PACMAN_UTILS_H

#include <utility>
#include <vector>
#include "../map/cell.h"
#include "json.hpp"

vector<CellType> loadCellTypesFromFile(const string &file_path);

#endif //PACMAN_UTILS_H
