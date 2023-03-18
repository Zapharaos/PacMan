//
// Created by matthieu on 07/02/2023.
//

#ifndef PACMAN_MAP_H
#define PACMAN_MAP_H

#include <vector>
#include <memory>
#include "cell.h"
#include "../entity/entity.h"
#include "../utils/direction.h"
#include "../display/animation.h"
#include "../utils/init_sprites.h"

/** The board of a game. */
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
     * @details Cells with entities are shared with cellsWithEntities_ member.
     */
    vector<shared_ptr<Cell>> cells_;

    /** Sub list of all cells with entities.
     * @details Shared with cells_ member.
     */
    vector<shared_ptr<Cell>> cellsWithEntities_;

    /** Current map sprite. */
    Sprite sprite_ {};

    /** Animation when level up. */
    Animation animation_ {};

public:

    /** Default Map constructor. */
    Map();

    /** Map constructor.
     *
     * @note cell_types can be loaded with Game::getCellsTypeFromFile()
     *
     * @param width Map's width.
     * @param height Map's height.
     * @param cell_size Width/height of the cells.
     * @param cell_types List of all cells type.
     */
    Map(int width, int height, int cell_size,
        const vector<CellType> &cell_types);

    /** Getter : Size of a cell. */
    [[nodiscard]] int getCellSize() const;

    /** Gets the cell at a given index position.
     *
     * @param position
     * @return the cell at position.
     */
    [[nodiscard]] shared_ptr<Cell> getCell(const Position &position) const;

    /** Getter : Sub list of all cells with entities. */
    [[nodiscard]] const vector<shared_ptr<Cell>> &getCellsWithEntities() const;

    /** If legal, turns into a direction.
      *
      * @details All positions are in pixels.
      *
      * @param origin Position of origin.
      * @param destination Position of destination.
      * @param direction Initial direction.
      * @param turn Direction wished for.
      *
      * @return the effective destination if the move is legal, else it returns nullptr.
      */
    [[nodiscard]] optional<Position>
    turnToCell(const Position &origin, const Position &destination, const Direction &direction,
               const Direction &turn) const;

    /** If legal, moves into a direction.
     *
     * @details All positions are in pixels.
     *
     * @param origin Position of origin.
     * @param destination Position of destination.
     * @param direction Initial direction.
     *
     * @return the effective destination if the move is legal, else it returns nullptr.
     */
    [[nodiscard]] optional<Position>
    moveToCell(const Position &origin, const Position &destination, const Direction &direction) const;

    /** Getter : Sprite's position on the bitmap.
     *
     * @see Sprite::getImage().
     */
    [[nodiscard]] const SDL_Rect &getSpriteImage() const;

    /** Getter : Sprite's position when displayed on the window.
     *
     * @see Sprite::getPosition().
     */
    [[nodiscard]] const SDL_Rect &getSpritePosition() const;

    /** Resets the map to its original state */
    void reset() const;

    /** Map blinking animation. */
    void animate();
};


#endif //PACMAN_MAP_H
