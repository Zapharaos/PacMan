//
// Created by matthieu on 07/02/2023.
//

#include "../../include/map/map.h"

// TODO : clean up
Sprite sprite_pellet{{constants::BMP_POINT_START_X,
                                 constants::BMP_POINT_START_Y,
                             constants::BMP_POINT_SIZE,
                             constants::BMP_POINT_SIZE},
                     {3 * 2 * 2, 3 * 2 * 2},
                     {2 * 2 * 2, 2 * 2 * 2}};

Sprite sprite_energizer{{constants::BMP_POWER_START_X,
                                    constants::BMP_POWER_START_Y,
                                constants::BMP_POWER_SIZE,
                                constants::BMP_POWER_SIZE},
                        {0,         0},
                        {7 * 2 * 2, 7 * 2 * 2}};

Map::Map() = default;

Map::Map(int width, int height, int cell_size,
         const vector<CellType> &cell_types) :
        width_(width), height_(height), cell_size_(cell_size)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            // shared_ptr<Song> p3(p2)
            Position position{{x, y}};
            CellType type = cell_types[x + width * y];
            if (type == CellType::PELLET)
            {
                Position coordinates{{x * cell_size_, y * cell_size_}};
                auto entity = make_shared<Entity>(Entity{coordinates, sprite_pellet, true, (int) Score::PELLET});
                auto cell = make_shared<Cell>(Cell{position, cell_size, type, entity});
                cells_.emplace_back(cell);
                cellsWithEntities_.emplace_back(cell);
            } else if (type == CellType::ENERGIZER)
            {
                Position coordinates{{x * cell_size_, y * cell_size_}};
                auto entity = make_shared<Entity>(Entity{coordinates, sprite_energizer, true, (int) Score::ENERGIZER});
                entity->count(30); // 60 fps => 15 shown - 15 hidden
                auto cell = make_shared<Cell>(Cell{position, cell_size, type, entity});
                cells_.emplace_back(cell);
                cellsWithEntities_.emplace_back(cell);
            }
            else {
                cells_.emplace_back(make_shared<Cell>(Cell{position, cell_size, type, nullptr}));
            }
        }
    }
}


int Map::getCellSize() const
{
    return cell_size_;
}

shared_ptr<Cell> Map::getCell(const Position &position) const
{
    if (position.isOutOfBounds(width_, height_))
        return nullptr;
    return cells_.at(position.getAbscissa() + position.getOrdinate() * width_);
}

const vector<shared_ptr<Cell>> &Map::getCellsWithEntities() const
{
    return cellsWithEntities_;
}

optional<Position>
Map::turnToCell(const Position &origin, const Position &destination, const Direction &direction,
                const Direction &turn) const
{
    // Get cells at origin & destination
    auto origin_position = origin.getPositionUnscaled(cell_size_);
    auto destination_position = destination.getPositionUnscaled(cell_size_);
    shared_ptr<Cell> origin_cell = getCell(origin_position);
    shared_ptr<Cell> destination_cell = getCell(destination_position);

    // Get turning position (edge)
    Position edge;
    if (direction.isLeftOrUp())
        edge = origin_cell->getPositionScaled();
    else
        edge = destination_cell->getPositionScaled();

    // Edge not between origin & destination : turn is illegal
    if (!edge.isBetween(origin, destination))
        return {};

    // Get the rest of the distance to travel
    int distance = origin.getSingleAxisDistance(destination) -
                   origin.getSingleAxisDistance(edge);

    // Move into new direction
    return moveToCell(edge, edge.moveIntoDirection(turn, distance), turn);
}

optional<Position>
Map::moveToCell(const Position &origin, const Position &destination, const Direction &direction) const
{

    // Get cells at origin & destination
    auto origin_position = origin.getPositionUnscaled(cell_size_);
    auto destination_position = destination.getPositionUnscaled(cell_size_);
    shared_ptr<Cell> origin_cell = getCell(origin_position);
    shared_ptr<Cell> destination_cell = getCell(destination_position);

    // Destination not directly accessible : move illegal
    if (origin_cell != destination_cell &&
        !destination_cell->isNeighbor((origin_cell.operator*())))
        return {};

    // Get next cell : in order to check for walls
    shared_ptr<Cell> next_cell;
    if (direction.isLeftOrUp())
        next_cell = destination_cell;
    else
        next_cell = getCell(origin_position.getNeighbor(direction));

    // Not a wall : move to destination
    if (!next_cell->isWall())
        return destination;

    // Facing wall & already in the corner of the cell : can't move further
    if (origin_cell->equalsPositionScaled(origin))
        return {};

    // Facing wall & not in the corner yet : get into the corner of the cell
    return origin_cell->getPositionScaled();
}

void Map::reset() const
{
    // Enables all cell entities back
    for (auto &cell: getCellsWithEntities())
        cell->getEntity()->setEnabled(true);
}
