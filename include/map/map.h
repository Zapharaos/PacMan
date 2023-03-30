/**
 * @file map.h
 * @brief Defines the Map class representing a map.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 07/02/2023
 */

#ifndef PACMAN_MAP_H
#define PACMAN_MAP_H

#include <vector>
#include <memory>

#include "../config/visuals.h"
#include "cell.h"
#include "../utils/direction.h"
#include "../display/animation.h"

/**
 * @brief The Map class represents the game board of a Pac-Man game.
 * This class manages the game board, which consists of a grid of cells.
*/
class Map
{

private:

    /** Map's width. */
    int width_ = 0;

    /** Map's height. */
    int height_ = 0;

    /** Width/height of the cells. */
    int cell_size_ = 0;

    /** List of all cells.
     * @details Cells with entities are shared with cellsWithEntities_ member. */
    std::vector<std::shared_ptr<Cell>> cells_;

    /** Sub list of all cells with entities.
     * @details Shared with cells_ member. */
    std::vector<std::shared_ptr<Cell>> cells_with_entities_;

    /** Current map sprite. */
    Sprite sprite_ {};

    /** Animation when level up. */
    Animation<visuals::map::kAnimationSize> animation_ {};

public:

    /**
     * @brief Default constructor for Map.
     */
    Map();

    /**
     * @brief Constructor for Map.
     * @note cell_types can be loaded with utils.h getCellsTypeFromFile()
     * @param cell_types List of all cells type.
     */
    explicit Map(const std::vector<CellType> &cell_types);

    /**
     * @brief Gets the size of a cell.
     * @return the size of a cell in pixels.
     */
    [[nodiscard]] int getCellSize() const;

    /**
     * @brief Gets the cell at a given index position.
     * @param position Position of the cell to get.
     * @return the cell at position.
     */
    [[nodiscard]] std::shared_ptr<Cell> getCell(const Position &position) const;

    /**
     * @brief Gets the sub list of all cells with entities.
     * @return the sub list of all cells with entities.
     */
    [[nodiscard]] const std::vector<std::shared_ptr<Cell>> &getCellsWithEntities() const;

    /**
     * @brief Getter for the sprite used to display the entity.
     * @return The new sprite used to display the entity.
     */
    [[nodiscard]] const Sprite &getSprite() const;

    /**
     * @brief If legal, turns into a direction.
     * @details All positions are in pixels.
     * @param origin Position of origin.
     * @param destination Position of destination.
     * @param direction Initial direction.
     * @param turn Direction wished for.
     * @return the effective destination if the move is legal, else it returns nullptr.
     */
    [[nodiscard]] std::optional<Position>
    turn(const Position &origin, const Position &destination, const Direction &direction,
               const Direction &turn) const;

    /**
     * @brief If legal, moves into a direction.
     * @details All positions are in pixels.
     * @param origin Position of origin.
     * @param destination Position of destination.
     * @param direction Initial direction.
     * @return the effective destination if the move is legal, else it returns nullptr.
     */
    [[nodiscard]] std::optional<Position>
    move(const Position &origin, const Position &destination, const Direction &direction) const;

    /**
     * @brief Tries to warp.
     * @param destination The destination position.
     * @param corner The opposite corner of the current position.
     * @return The position after trying to warp.
     */
    [[nodiscard]] std::optional<Position> warp(Position destination, Position corner) const;

    /**
     * @brief Checks if a move would result in warping to another part of the map.
     * @param origin Position of origin.
     * @param destination Position of destination.
     * @return true if warp, else false.
     */
    [[nodiscard]] bool isWarping(const Position &origin, const Position &destination) const;

    /**
     * @brief Resets all cells on the map to their original state.
     */
    void reset() const;

    /**
     * @brief Animates the Map sprite with a blinking effect to indicate level up.
     */
    void animate();
};


#endif //PACMAN_MAP_H
