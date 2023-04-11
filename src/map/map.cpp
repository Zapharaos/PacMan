/**
 * @file map.cpp
 * @brief Implementation of the the Map class representing a map.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 07/02/2023
 */

#include "../../include/map/map.h"

Map::Map() = default;

Map::Map(const std::vector<CellType> &cell_types) {
    width_ = config::dimensions::kMapWidth;
    height_ = config::dimensions::kMapHeight;
    cell_size_ = config::dimensions::kWindowCellSize;
    animation_ = visuals::map::kAnimation;
    sprite_ = animation_.getSprite();

    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            Position position{{x, y}};
            auto type = cell_types[x + width_ * y];

            if(type == CellType::kGhostOnlyHorizontalAndPellet || type == CellType::kGhostOnlyHorizontal)
                type = type;

            // Not a pellet and not an energizer => trivial.
            if (type != CellType::kPellet && type != CellType::kEnergizer
                && type != CellType::kGhostOnlyHorizontalAndPellet) {
                cells_.emplace_back(std::make_shared<Cell>(
                        Cell{position, cell_size_, type, nullptr}));
                continue;
            }

            Position coordinates{{x * cell_size_, y * cell_size_}};
            std::shared_ptr<Entity> entity;

            if (type == CellType::kPellet ||
                type == CellType::kGhostOnlyHorizontalAndPellet) {
                entity = std::make_shared<Entity>(
                        Entity{coordinates, visuals::pellet::kSprite, true,
                               static_cast<int> (Score::kPellet)});
            } else {
                entity = std::make_shared<Entity>(
                        Entity{coordinates, visuals::energizer::kSprite, true,
                               static_cast<int> (Score::kEnergizer)});
                entity->count(config::settings::kRefreshRateTicksEnergizer);
            }

            auto cell = std::make_shared<Cell>(
                    Cell{position, cell_size_, type, entity});
            cells_.emplace_back(cell);
            cells_with_entities_.emplace_back(cell);
        }
    }
}


int Map::getCellSize() const {
    return cell_size_;
}

std::shared_ptr<Cell> Map::getCell(const Position &position) const {
    if (position.isOutOfBounds(width_, height_))
        return nullptr;
    return cells_.at(position.getAbscissa() + position.getOrdinate() * width_);
}

const std::vector<std::shared_ptr<Cell>> &Map::getCellsWithEntities() const {
    return cells_with_entities_;
}

const Sprite &Map::getSprite() const {
    return sprite_;
}

std::optional<Position>
Map::turn(const Position &origin, const Position &destination,
          const Direction &direction, const Direction &turn,
          bool zone_horizontal_only, bool ghost_house_door_access) const
{
    // Can't turn while warping.
    if(isWarping(origin, destination))
        return {};

    // Get cells at origin & destination
    auto origin_position = origin.scaleDown(cell_size_);
    auto destination_position = destination.scaleDown(cell_size_);
    auto origin_cell = getCell(origin_position);
    auto destination_cell = getCell(destination_position);

    // Get turning position (edge)
    Position edge;
    if (direction.isLeftOrUp())
        edge = origin_cell->positionToPixels();
    else
        edge = destination_cell->positionToPixels();

    // Edge not between origin & destination : turn is illegal
    if (!edge.isBetween(origin, destination))
        return {};

    // Get the rest of the distance to travel
    auto distance = origin.getSingleAxisDistance(destination) -
                    origin.getSingleAxisDistance(edge);

    // Move into new direction
    return move(edge, edge.moveIntoDirection(turn, distance), turn, zone_horizontal_only, ghost_house_door_access);
}

std::optional<Position>
Map::move(const Position &origin, const Position &destination,
          const Direction &direction, bool zone_horizontal_only, bool ghost_house_door_access) const {

    // One of the cells is out of bounds : warp cell.
    if(isWarping(origin, destination))
        return destination;

    // Get cells at origin & destination
    auto origin_position = origin.scaleDown(cell_size_);
    auto destination_position = destination.scaleDown(cell_size_);
    auto origin_cell = getCell(origin_position);
    auto destination_cell = getCell(destination_position);

    // Destination not directly accessible : move illegal
    if (origin_cell != destination_cell &&
        !destination_cell->isNeighbor((origin_cell.operator*())))
        return {};

    if(zone_horizontal_only && direction.isVertical() && origin_cell->isGhostHorizontal())
        return {};

    // Get next cell : in order to check for walls
    auto next_cell = direction.isLeftOrUp() ? destination_cell :
            getCell(origin_position.getNeighbor(direction));

    if(!ghost_house_door_access && next_cell && next_cell->isGhostHouseDoor())
        return {};

    // Ouf of bounds (warp) or is not a wall : move to destination
    if (!next_cell || !next_cell->isWall())
            return destination;

    // Facing wall & already in the corner of the cell : can't move further
    if (origin == origin_cell->positionToPixels())
        return {};

    // Facing wall & not in the corner yet : get into the corner of the cell
    return origin_cell->positionToPixels();
}

std::optional<Position> Map::warp(Position destination, Position corner) const {
    auto destination_position = destination.scaleDown(cell_size_);
    auto corner_position = corner.scaleDown(cell_size_);
    auto destination_cell = getCell(destination_position);
    auto corner_cell = getCell(corner_position);

    // Positions are completely out ouf bounds, time to warp.
    if (destination_cell == nullptr && corner_cell == nullptr)
        return destination.getOpposite(width_ * cell_size_,
                                       height_ * cell_size_);

    // Keep moving until the warp position is reached.
    return destination;
}

bool Map::isWarping(const Position &origin, const Position &destination) const {
    // Get cells at origin & destination
    auto origin_position = origin.scaleDown(cell_size_);
    auto destination_position = destination.scaleDown(cell_size_);
    auto origin_cell = getCell(origin_position);
    auto destination_cell = getCell(destination_position);

    // Destination must be out of bounds to be considered as a warp.
    // Origin must be either a warp cell or out of bound as well.
    return (!origin_cell || origin_cell->isWarp()) && !destination_cell;
}

void Map::reset() const {
    // Enables all cell entities back
    for (auto &cell: getCellsWithEntities())
        cell->getEntity()->setEnabled(true);
}

void Map::animate() {
    sprite_ = animation_.animate();
}

std::set<Direction>
Map::getAvailableDirections(const std::shared_ptr<Cell>& cell, const Direction &direction,
                            bool zone_horizontal_only, bool ghost_house_door_access) const {
    std::set<Direction> directions;
    if(!cell) return directions;
    auto position = cell->getPosition();
    zone_horizontal_only = cell->isGhostHorizontal() && zone_horizontal_only;
    for (auto &element: Direction::directions) {
        Direction element_direction = Direction{element};
        if (element_direction == direction.reverse()) // Instant reverse not allowed
            continue;
        auto neighbor = getCell(position.getNeighbor(element_direction));
        // Cell not reachable or special zone where ghosts only move horizontally
        if (!neighbor || neighbor->isWall() ||
                (!ghost_house_door_access && neighbor->isGhostHouseDoor()) ||
                (zone_horizontal_only && element_direction.isVertical()))
            continue;
        directions.insert(directions.end(), element_direction);
    }
    return directions;
}


Position Map::calculateDestination(const Position &origin, const Direction &direction, int speed, bool zone_tunnel_slow) const
{
    auto cell = getCell(origin.scaleDown(cell_size_));
    if(cell && cell->isTunnel() && zone_tunnel_slow)
        speed /= config::settings::kSpeedDownRatio;
    return origin.moveIntoDirection(direction, speed);
}
