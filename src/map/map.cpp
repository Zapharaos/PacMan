//
// Created by matthieu on 07/02/2023.
//

#include <iostream>
#include <cmath>
#include "../../include/map/map.h"

Map::Map() = default;

Map::Map(int width, int height, int cell_size, const std::vector<CellType>& cell_types) : width_(width), height_(height), cell_size_(cell_size)
{
    Sprite point {{ constants::BMP_POINT_START_X,constants::BMP_POINT_START_Y, constants::BMP_POINT_SIZE,constants::BMP_POINT_SIZE }, {}};
    Sprite power {{ constants::BMP_POWER_START_X,constants::BMP_POWER_START_Y, constants::BMP_POWER_SIZE,constants::BMP_POWER_SIZE }, {}};

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Entity entity = {};
            CellType type = cell_types[x + width * y];
            if(type == CellType::PELLET) {
                std::pair<int, int> coordinates = {x * cell_size_ + constants::WINDOW_POINTS_OFFSET, y * cell_size_ + constants::WINDOW_POINTS_OFFSET};
                entity = {coordinates, constants::WINDOW_POINTS_SIZE, point, (int) Score::PELLET, false};
            } else if(type == CellType::ENERGIZER) {
                std::pair<int, int> coordinates = {x * cell_size_ + constants::WINDOW_POWER_OFFSET, y * cell_size_ + constants::WINDOW_POWER_OFFSET};
                entity = {coordinates, constants::WINDOW_POWER_SIZE, power, (int) Score::ENERGIZER, false};
            }
            cells_.emplace_back(Cell{{x, y}, cell_size, type, entity});
        }
    }
}

bool Map::canTurnToCell(std::pair<int, int> origin, std::pair<int, int> destination, Direction direction, Direction turn) {

    bool toFloor = (direction == Direction::LEFT || direction == Direction::UP);
    Cell destination_cell = getCellFromCoordinates(destination, toFloor);

    if(destination_cell.isWall()) // check if facing a wall
    {
        int remainder = getRemainder(origin, origin, destination, direction);
        destination = changeDestinationOnTurn(origin, remainder, turn);
        return canMoveToCell(origin, destination, turn);
    }

    Cell origin_cell = getCellFromCoordinates(origin, true);
    destination_cell = getCellFromCoordinates(destination, !toFloor);
    std::pair<int, int> edge = destination_cell.getScaledPosition();

    // if edge is between origin & destination
    if(!isPositionInBetween(direction, edge, origin, destination))
        return false;

    int remainder = getRemainder(origin, edge, destination, direction);
    destination = changeDestinationOnTurn(edge, remainder, turn);
    return canMoveToCell(edge, destination, turn);
}

bool Map::canMoveToCell(std::pair<int, int> origin, std::pair<int, int> destination, Direction direction) {

    bool toFloor = (direction == Direction::LEFT || direction == Direction::UP);

    Cell exit = getWarpExitCell(destination, toFloor);
    if(exit.isWarp()) // if the exit cell has been reached
    {
        destination_ = exit.getWarpExit(width_, height_);
        return true;
    }

    Cell entry = getWarpEntryCell(origin, toFloor);
    if(entry.isWarp() && hasExit(entry)) // allow moving out of bounds
    {
        destination_ = destination;
        return true;
    }

    Cell origin_cell = getCellFromCoordinates(origin, toFloor);
    Cell destination_cell = getCellFromCoordinates(destination, toFloor);

    if(!destination_cell.isAlignedWith(destination)) return false;

    destination_ = destination;

    if(!destination_cell.isWall()) return true; // is not a wall
    if(origin_cell.equalsScaledPosition(origin)) return false; // is already next to the wall
    destination_ = origin_cell.getScaledPosition(); // move next to the wall
    return true;
}

Cell& Map::getCellAtPosition(std::pair<int, int> position) {
    return cells_[position.first + position.second * width_];
}

const std::pair<int, int> &Map::getDestination() const {
    return destination_;
}

std::vector<Cell> Map::getCellsWithActiveEntities() {
    std::vector<Cell> cells;
    for(auto & cell : cells_)
        if(!cell.getEntity().isDisabled())
            cells.emplace_back(cell);
    return cells;
}

bool Map::isPositionInBetween(Direction direction, std::pair<int, int> position, std::pair<int, int> origin, std::pair<int, int> destination) {
    bool from_left = (origin.first <= position.first && position.first < destination.first);
    bool from_right = (destination.first < position.first && position.first <= origin.first);
    bool from_up_ = (origin.second <= position.second && position.second < destination.second);
    bool from_bottom_ = (destination.second < position.second && position.second <= origin.second);

    switch(direction) {
        case Direction::LEFT:
            return from_right;
        case Direction::RIGHT:
            return from_left;
        case Direction::UP:
            return from_bottom_;
        case Direction::DOWN:
            return from_up_;
        default:
            return false;
    }
}

int Map::getRemainder(pair<int, int> origin, pair<int, int> middle, pair<int, int> destination, Direction direction) {
    switch(direction) {
        case Direction::LEFT:
            return (origin.first - destination.first) - (origin.first - middle.first);
        case Direction::RIGHT:
            return (destination.first - origin.first) - (middle.first - origin.first);
        case Direction::UP:
            return (origin.second - destination.second) - (origin.second - middle.second);
        case Direction::DOWN:
            return (destination.second - origin.second) - (middle.second - origin.second);
        default:
            return 0;
    }
}

pair<int, int> Map::changeDestinationOnTurn(pair<int, int> origin, int remainder, Direction direction)
{
    pair<int, int> destination = origin;
    switch(direction) {
        case Direction::LEFT:
            destination.first -= remainder;
            break;
        case Direction::RIGHT:
            destination.first += remainder;
            break;
        case Direction::UP:
            destination.second -= remainder;
            break;
        case Direction::DOWN:
            destination.second += remainder;
            break;
        default:
            break;
    }
    return destination;
}

Cell& Map::getCellFromCoordinates(pair<int, int> coordinates, bool toFloor)
{
    return getCellAtPosition(getPositionFromCoordinates(coordinates, toFloor));
}

pair<int, int> Map::getPositionFromCoordinates(pair<int, int> coordinates, bool toFloor) const
{
    std::pair<int, int> scaled;
    float x = (float) coordinates.first / (float) cell_size_;
    float y = (float) coordinates.second / (float) cell_size_;
    if(toFloor) {
        scaled.first = std::floor(x);
        scaled.second = std::floor(y);
    } else {
        scaled.first = std::ceil(x);
        scaled.second = std::ceil(y);
    }
    return scaled;
}

Cell Map::getWarpEntryCell(pair<int, int> coordinates, bool toFloor) {
    std::pair<int, int> position = getPositionFromCoordinates(coordinates, toFloor);

    if(position.first == -1)
        position.first = 0;
    else if(position.first == width_)
        position.first = width_-1;
    else if(position.second == -1)
        position.second = 0;
    else if(position.second == height_)
        position.second = height_-1;

    return getCellAtPosition(position);
}

Cell Map::getWarpExitCell(pair<int, int> coordinates, bool toFloor) {
    std::pair<int, int> position = getPositionFromCoordinates(coordinates, toFloor);

    if(position.first == -2)
        position.first = width_-1;
    else if(position.first == width_+1)
        position.first = 0;
    else if(position.second == -2)
        position.second = height_-1;
    else if(position.second == height_+1)
        position.second = 0;
    else
        return {};

    return getCellAtPosition(position);
}

bool Map::hasExit(const Cell& cell) {
    return getCellFromCoordinates(cell.getWarpExit(width_, height_), true).isWarp();
}
