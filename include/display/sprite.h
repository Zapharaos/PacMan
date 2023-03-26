/**
 * @file sprite.h
 * @brief Contains the Sprite class which represents an object displayed on the window.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 01/03/2023
*/

#ifndef PACMAN_SPRITE_H
#define PACMAN_SPRITE_H

#include <SDL_rect.h>

#include <utility>

#include "../map/position.h"

/**
 * @brief Represents an object displayed on the window.
 * This class is responsible for defining and updating the position of an object on the screen.
*/
class Sprite
{

private:

    /** Position on the bitmap. */
    SDL_Rect image_{};

    /** Position when displayed on the window. */
    SDL_Rect position_{};

    /** Offset when displayed on the window. */
    std::pair<int, int> offset_{};

    /** Size when displayed on the window. */
    std::pair<int, int> size_{};

public:

    /**
     * @brief Default constructor for the Sprite class.
     */
    inline constexpr Sprite() = default;

    /**
     * @brief Constructor for the Sprite class.
     * @param image Position on the bitmap.
     * @param offset Offset when displayed on the window.
     * @param size Size when displayed on the window.
     */
    inline constexpr Sprite(SDL_Rect image, std::pair<int, int> offset, std::pair<int, int> size) : image_(image), offset_(std::move(offset)), size_(std::move(size)) {
        position_ = {offset_.first, offset_.second, size_.first, size_.second};
    }

    /**
     * @brief Getter function for the position of the image on the bitmap.
     * @return A constant reference to the position of the image on the bitmap.
     */
    [[nodiscard]] inline const SDL_Rect &getImage() const
    { return image_; };


    /**
     * @brief Getter function for the position of the sprite when displayed on the window.
     * @return A constant reference to the position of the sprite when displayed on the window.
     */
    [[nodiscard]] const SDL_Rect &getPosition() const
    { return position_; };

    /**
     * @brief Updates the position of the sprite when displayed on the window.
     * @param coordinates Raw position of the sprite when displayed on the window.
     */
    void updatePosition(const Position &coordinates)
    {
        position_ = {coordinates.getAbscissa() + offset_.first,
                     coordinates.getOrdinate() + offset_.second,
                     size_.first,
                     size_.second};
    };

};


#endif //PACMAN_SPRITE_H
