//
// Created by matthieu on 07/02/2023.
//

#include <iostream>
#include <cmath>
#include "../include/map.h"
#include "../include/constants.h"

Map::Map() = default;

Map::Map(int width, int height, int cell_size, const std::vector<int>& cell_types) : width_(width), height_(height), cell_size_(cell_size)
{
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            cells_.emplace_back(Cell{x, y, cell_types[x + width * y] == constants::CELL_TYPE_WALL});
}

void Map::print() const
{
    std::cout << "width: " << width_ << ", height: " << height_ << ", cells: " << std::endl;
    for(const auto& cell: cells_) cell.print();
}

void Map::printAsMap() const
{
    for (int y = 0; y < height_; y++)
    {
        for (int x = 0; x < width_; x++)
        {
            std::cout << (cells_[x + width_ * y].isWall() ? " " : "1") << " ";
        }
        std::cout << std::endl;
    }
}

bool Map::canMoveToCell(std::pair<int, int> destination, bool isMovingLeftOrUp) {
    if(!isDirectNeighbour(destination)) return false;
    std::pair<int, int> scaled = getCellCoordinatesFromPositions(destination, isMovingLeftOrUp);
    if(isTunnel(scaled))
    {
        destination_ = getTunnelCoordinates(destination);
        return true;
    }
    if(isPositionOutOfBounds(scaled)){
        std::cerr << "canMoveToCell : Position out of bounds" << std::endl;
        return false;
    }
    destination_ = destination;
    return !getCellAtPosition(scaled).isWall();
}

float Map::getScaledPosition(int position) const {
    return (float) position / (float) cell_size_;
}

std::pair<int, int> Map::getCellCoordinatesFromPositions(std::pair<int, int> destination, bool isMovingLeftOrUp) {
    std::pair<int, int> scaled;
    float x = getScaledPosition(destination.first);
    float y = getScaledPosition(destination.second);
    if(isMovingLeftOrUp) {
        scaled.first = std::floor(x);
        scaled.second = std::floor(y);
    } else {
        scaled.first = std::ceil(x);
        scaled.second = std::ceil(y);
    }
    return scaled;
}

bool Map::isPositionOutOfBounds(std::pair<int, int> position) const {
    if(position.first < 0 || position.second < 0) return true;
    if(position.first > width_ || position.second > height_) return true;
    return false;
}

int Map::getCellIndexFromPosition(std::pair<int, int> position) const {
    return position.first + position.second * width_;
}

Cell Map::getCellAtPosition(std::pair<int, int> position) const {
    return cells_[getCellIndexFromPosition(position)];
}

bool Map::isDirectNeighbour(std::pair<int, int> destination) const {
    float x = getScaledPosition(destination.first);
    float y = getScaledPosition(destination.second);
    return(x == std::floor(x) || y == std::floor(y));
}

const std::pair<int, int> &Map::getDestination() const {
    return destination_;
}

bool Map::isTunnel(std::pair<int, int> position) const {
    return (position.first == -1 || position.first == width_ || position.second == -1 || position.second == height_);
}

std::pair<int, int> Map::getTunnelCoordinates(std::pair<int, int> destination) const {
    if(destination.first < 0)
        destination.first = (width_ - 1) * cell_size_;
    else if(destination.first > (width_ - 1) * cell_size_)
        destination.first = 0;
    else if(destination.second < 0)
        destination.second = (height_ - 1) * cell_size_;
    else if(destination.second > (height_ - 1) * cell_size_)
        destination.second = 0;
    return destination;
}
