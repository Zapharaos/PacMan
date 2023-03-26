/**
 * @file cell.h
 * @brief Contains the Cell class representing an element on a map.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 07/02/2023
 */

#ifndef PACMAN_CELL_H
#define PACMAN_CELL_H

#include <string>
#include <array>
#include <optional>
#include <memory>

#include "../entity/entity.h"
#include "position.h"

/**
 * @brief Indicates the cell type (i.e. what it represents).
*/
enum class CellType
{
    kWall, /* Wall type cell */
    kPellet, /* Pellet type cell */
    kEnergizer, /* Energizer type cell */
    kPath, /* Path type cell */
    kWarp /* Warp type cell */
};

/**
 * @brief Represents a cell on the game board.
 * A cell is an element on the game board with a type and position. It can also have an optional entity associated to it.
*/
class Cell
{

private:

    /** Position on the board. */
    Position position_{};

    /** Size in pixels.
     * @note width and height are equals. */
    int size_{};

    /** Type of cell. */
    CellType type_ = CellType::kWall;

    /** Entity associated to the cell.
     * @details Optional. */
    std::shared_ptr<Entity> entity_{};

public:

    /**
     * @brief Default constructor for the Cell class.
     */
    inline Cell() = default;

    /**
     * @brief Constructor for the Cell class.
     * @param position Position on the board.
     * @param size Size in pixels.
     * @param type Type of cell.
     * @param entity Entity associated with the cell.
     */
    Cell(Position position, int size, const CellType &type,
         std::shared_ptr<Entity> entity) :
            position_(std::move(position)), size_(size), type_(type), entity_(std::move(entity))
    {};

    /**
     * @brief Equality comparison operator.
     * @param cell Cell to compare with.
     * @return true if the cells are equal, false otherwise.
     */
    inline bool operator==(const Cell &cell) const
    { return position_ == cell.position_; };

    /**
     * @brief Inequality comparison operator.
     * @param cell Cell to compare with.
     * @return true if the cells are different, false otherwise.
     */
    inline bool operator!=(const Cell &cell) const
    { return !(cell == *this); };

    /**
     * @brief Check if the cell is a wall.
     * @return true if the cell is a wall, false otherwise.
     */
    [[nodiscard]] inline bool isWall() const
    { return type_ == CellType::kWall; };

    /**
     * @brief Check if the cell is a warp.
     * @return true if the cell is a warp, false otherwise.
     */
    [[nodiscard]] inline bool isWarp() const
    { return type_ == CellType::kWarp; };

    /**
     * @brief Getter for the type of cell.
     * @return Type of cell.
     */
    [[nodiscard]] inline const CellType &getType() const
    { return type_; };

    /**
     * @brief Getter for the entity associated with the cell.
     * @return Optional entity.
     */
    [[nodiscard]] inline const std::shared_ptr<Entity> &getEntity() const
    { return entity_; };

    /**
     * @brief Check if a cell is a neighbor of this cell.
     * @param cell The cell to check.
     * @return true if the cell is a neighbor, false otherwise.
     */
    [[nodiscard]] inline bool isNeighbor(const Cell &cell) const
    { return position_.isNeighbor(cell.position_); };

    /**
     * @brief Check if a position fits perfectly on the cell.
     * @param position Position in pixels.
     * @return true if the position fits perfectly on the cell, false otherwise.
     */
    [[nodiscard]] inline bool equalsPositionScaled(const Position &position) const
    { return position == getPositionScaled(); };

    /**
     * @brief Returns the cell's position in pixels.
     * @return The cell's position in pixels.
     */
    [[nodiscard]] Position getPositionScaled() const
    { return position_.getPositionScaled(size_); };

    /**
     * @brief Prints the cell's members.
     * @details This function is intended for debugging purposes.
     */
    void print() const
    {
        position_.print();
        position_.getPositionScaled(size_).print();
        std::cout << static_cast<std::underlying_type<CellType>::type>(type_) << std::endl;
        entity_->print();
    };
};


#endif //PACMAN_CELL_H
