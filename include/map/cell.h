//
// Created by matthieu on 07/02/2023.
//

#ifndef PACMAN_CELL_H
#define PACMAN_CELL_H

#include <string>
#include <array>
#include <optional>
#include <memory>
#include "../utils/constants.h"
#include "../entity/entity.h"
#include "position.h"

/** Indicates the cell type (i.e. what it represents). */
enum class CellType
{
    WALL,
    PELLET,
    ENERGIZER,
    PATH,
    WARP
};

/** Cell inside on a board. */
class Cell
{

private:

    /** Position on the board. */
    Position position_{};

    /** Size in pixels. */
    int size_{};

    /** Type of cell. */
    CellType type_ = CellType::WALL;

    /** Entity associated to the cell.
     * @details Optional.
     */
    shared_ptr<Entity> entity_{};

public:

    /** Default Cell constructor. */
    Cell();

    /** Cell constructor.
     *
     * @param position Position on the board.
     * @param size Size in pixels.
     * @param type Type of cell.
     * @param entity Entity associated to the cell.
     */
    Cell(Position position, int size, const CellType &type,
         const shared_ptr<Entity> &entity);

    /** If both cells are equals. */
    bool operator==(const Cell &rhs) const;

    /** If both cells are different. */
    bool operator!=(const Cell &rhs) const;

    /** If the cell is a wall. */
    [[nodiscard]] inline bool isWall() const
    { return type_ == CellType::WALL; };

    /** If the cell is a warp. */
    [[nodiscard]] inline bool isWarp() const
    { return type_ == CellType::WARP; };

    /** Getter : Type of cell. */
    [[nodiscard]] const CellType &getType() const;

    /** Getter : Entity associated to the cell.
     * @return Optional entity.
     */
    [[nodiscard]] const shared_ptr<Entity> &getEntity() const;

    /** Indicates if a cell is a neighbor.
     *
     * @param cell The second cell.
     * @return true if it's a neighbor, else false.
     */
    [[nodiscard]] bool isNeighbor(const Cell &cell) const;

    /** If a position fits perfectly on the cell.
     *
     * @param position Position in pixels.
     * @return true if both pixel positions are equals.
     */
    [[nodiscard]] bool equalsPositionScaled(const Position &position) const;

    /** Returns the cell's position in pixels. */
    [[nodiscard]] Position getPositionScaled() const;

    /** [Debug] : Prints the cell's members. */
    void print() const;
};


#endif //PACMAN_CELL_H
