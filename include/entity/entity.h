/**
 * @file entity.h
 * @brief Defines the Entity class, an object located on the map.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 08/02/2023
*/

#ifndef PEC_MEN_ENTITY_H
#define PEC_MEN_ENTITY_H

#include <SDL.h>

#include <string>
#include <iostream>
#include <utility>

#include "../display/sprite.h"
#include "../utils/counter.h"

/**
 * @brief An object located on the map.
 */
class Entity
{

protected:

    /*
     * @brief EntityStatus enumeration.
     * Defines entity visibility status.
     */
    enum class EntityStatus {
        kVisible, /* Entity is visible. */
        kHidden /* Entity is hidden. */
    };

    /** Counts a number of frames. */
    Counter counter_ {};

    /** Entity status. */
    EntityStatus status_ {EntityStatus::kVisible};

private:

    /** Raw position. */
    Position position_{};

    /** Image when displayed. */
    Sprite sprite_{};

    /** If the entity is active. */
    bool enabled_ = false;

    /** Points earned when entity is eaten. */
    int points_{};

public:

    /**
     * @brief Default constructor for Entity.
     */
    Entity();

    /**
     * @brief Constructor for Entity.
     * @param position The raw position of the entity.
     * @param sprite The sprite used to display the entity.
     * @param enabled Indicates if the entity is enabled.
     * @param points The number of points earned when the entity is eaten.
     */
    Entity(Position position, Sprite sprite, bool enabled, int points);

    /**
     * @brief Constructor for Entity.
     * @param position The raw position of the entity.
     * @param sprite The sprite used to display the entity.
     */
    Entity(Position position, Sprite sprite);

    /**
     * @brief Constructor for Entity.
     * @param position The raw position of the entity.
     */
    explicit Entity(Position position);

    /**
     * @brief Getter for the raw position of the entity.
     * @return The raw position of the entity.
     */
    [[nodiscard]] const Position &getPosition() const;

    /**
     * @brief Setter for the raw position of the entity.
     * @param position The new raw position of the entity.
     */
    void setPosition(const Position &position);

    /**
     * @brief Setter for the sprite used to display the entity.
     * @param sprite The new sprite used to display the entity.
     */
    void setSprite(const Sprite &sprite);

    /**
     * @brief Getter for the number of points earned when the entity is eaten.
     * @return The number of points earned when the entity is eaten.
     */
    [[nodiscard]] int getPoints() const;

    /**
     * @brief Setter for the number of points earned when the entity is eaten.
     * @param points The new number of points earned when the entity is eaten.
     */
    void setPoints(int points);

    /**
     * @brief Getter for whether the entity is enabled.
     * @return True if the entity is enabled, false otherwise.
     */
    [[nodiscard]] bool isEnabled() const;

    /**
     * @brief Setter for entity status.
     * @param enabled Entity status.
     */
    void setEnabled(bool enabled);

    /**
     * @brief Getter for sprite image position.
     * @return const SDL_Rect& Sprite's image position on the bitmap.
     * @see Sprite::getImage().
     */
    [[nodiscard]] const SDL_Rect &getSpriteImage() const;

    /**
     * @brief Getter for sprite's display position.
     * @return const SDL_Rect& Sprite's position when displayed on the window.
     * @see Sprite::getPosition().
     */
    [[nodiscard]] const SDL_Rect &getSpritePosition() const;

    /**
     * @brief Getter for sprite's display size.
     * @return std::pair<int, int> Sprite's size when displayed on the window.
     */
    [[nodiscard]] std::pair<int, int> getSpriteSize() const;

    /**
     * @brief Count for a certain amount of frames.
     * @param frames Amount of frames.
     * @see Counter::start()
     */
    void count(long frames);

    /**
     * @brief Hide entity.
     */
    void hide();

    /**
     * @brief Show entity.
     */
    void show();

    /**
     * @brief Indicates if the entity is visible.
     * @return bool True if visible, else false.
     */
    bool isVisible();

    /**
     * @brief Toggles the entity status and its visibility according to the counter member.
     * @return bool True if visible, false if hidden.
     */
    bool tickVisibility();

    /**
     * @brief Prints entity's members for debugging purposes.
     */
    void print() const;
};

#endif //PEC_MEN_ENTITY_H
