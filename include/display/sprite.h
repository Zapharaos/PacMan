//
// Created by matthieu on 01/03/2023.
//

#ifndef PACMAN_SPRITE_H
#define PACMAN_SPRITE_H

#include <SDL_rect.h>

#include "../map/position.h"

/** Object displayed on the window. */
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

    /** Default Sprite constructor. */
    Sprite();

    /** Sprite constructor.
     *
     * @param image Position on the bitmap.
     * @param offset Offset when displayed on the window.
     * @param size Size when displayed on the window.
     */
    Sprite(const SDL_Rect &image, std::pair<int, int> offset, std::pair<int, int> size);

    /** Getter : Position on the bitmap. */
    [[nodiscard]] const SDL_Rect &getImage() const;

    /** Getter : Position when displayed on the window. */
    [[nodiscard]] const SDL_Rect &getPosition() const;

    /** Updates the position when displayed on the window.
     *
     * @param coordinates Raw position when displayed on the window.
     */
    void updatePosition(const Position &coordinates);

};


#endif //PACMAN_SPRITE_H
