/**
 * @file entity.h
 * @brief Defines the Entity class, an object located on the map.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 08/02/2023
*/

#ifndef PACMAN_ENTITY_H
#define PACMAN_ENTITY_H

#include <SDL.h>

#include <string>
#include <iostream>
#include <utility>

#include "../display/sprite.h"
#include "../utils/counter.h"
#include "../config/config.h"

/**
 * @brief An object located on the map.
 */
class Entity
{

private:

    /**
     * @brief EntityStatus enumeration.
     * Defines Entity status.
     */
    enum class EntityStatus {
        kShown, /* Entity is shown. */
        kShownTimed, /* Entity is timed shown. */
        kHidden, /* Entity is hidden. */
        kDead, /* Entity is dead. */
        kFrozen /* Entity is frozen. */
    };

    /** Entity status. */
    EntityStatus status_ {EntityStatus::kShown};

    /** Counts a number of frames. */
    Counter status_counter_ {};

    /** If the Entity is active. */
    bool enabled_ = false;

    /** Raw position. */
    Position position_{};

    /** Raw size. */
    int size_{config::dimensions::kMovingEntitySize};

    /** Image when displayed. */
    Sprite sprite_{};

    /** Points earned when Entity is eaten. */
    unsigned long points_{};

    /**
     * True if the Entity alternate between shown and hidden, otherwise false.
     */
    bool blinking_{};

public:

    /**
     * @brief Default constructor for Entity.
     */
    Entity();

    /**
     * @brief Constructor for Entity.
     * @param position The raw position of the Entity.
     */
    explicit Entity(Position position);

    /**
     * @brief Constructor for Entity.
     * @param position The raw position of the Entity.
     * @param sprite The sprite used to display the Entity.
     */
    Entity(Position position, Sprite sprite);

    /**
     * @brief Constructor for Entity.
     * @param position The raw position of the Entity.
     * @param sprite The sprite used to display the Entity.
     * @param enabled Indicates if the Entity is enabled.
     * @param points The number of points earned when the Entity is eaten.
     */
    Entity(Position position, Sprite sprite, bool enabled, int points);

    /**
     * @brief Constructor for Entity.
     * @param position The raw position of the Entity.
     * @param sprite The sprite used to display the Entity.
     * @param enabled Indicates if the Entity is enabled.
     * @param points The number of points earned when the Entity is eaten.
     * @param blinking_ticks True if the Entity alternate between shown and hidden, otherwise false. When different from 0, it sets the blinking_ member to true.
     */
    Entity(Position position, Sprite sprite, bool enabled, int points, unsigned long blinking_ticks);

    /**
     * @brief Getter for whether the Entity is enabled.
     * @return True if the entity is Entity, otherwise false.
     */
    [[nodiscard]] bool isEnabled() const;

    /**
     * @brief Setter for whether the Entity is enabled.
     * @param enabled True if the Entity is enabled, otherwise false.
     */
    void setEnabled(bool enabled);

    /**
     * @brief Getter for the raw position of the Entity.
     * @return The raw position of the Entity.
     */
    [[nodiscard]] const Position &getPosition() const;

    /**
     * @brief Setter for the raw position of the Entity.
     * @param position The new raw position of the Entity.
     */
    void setPosition(const Position &position);

    /**
     * @brief Getter for the raw size of the Entity.
     * @return The raw size of the Entity.
     */
    [[nodiscard]] int getSize() const;

    /**
     * @brief Getter for the sprite used to display the Entity.
     * @return The new sprite used to display the Entity.
     */
    [[nodiscard]] const Sprite &getSprite() const;

    /**
     * @brief Setter for the sprite used to display the Entity.
     * @param sprite The new sprite used to display the Entity.
     */
    void setSprite(const Sprite &sprite);

    /**
     * @brief Getter for the number of points earned when the Entity is eaten.
     * @return The number of points earned when the Entity is eaten.
     */
    [[nodiscard]] unsigned long getPoints() const;

    /**
     * @brief Setter for the number of points earned when the Entity is eaten.
     * @param points The new number of points earned when the Entity is eaten.
     */
    void setPoints(unsigned long points);

    /**
     * @brief Hide Entity.
     */
    void hide();

    /**
     * @brief Show Entity.
     */
    void show();

    /**
     * @brief Show Entity for a limited amount of time.
     * @param ticks Amount of ticks for which the Entity is shown.
     */
    void showTimed(unsigned long ticks);

    /**
     * @brief Kill Entity.
     */
    virtual void kill();

    /**
     * @brief Freeze Entity.
     * @param ticks The freeze duration.
     */
    void freeze(unsigned long ticks = 0);

    /**
     * @brief Indicates if the Entity is shown.
     * @return True if shown, otherwise false.
     */
    [[nodiscard]] bool isShown() const;

    /**
     * @brief Indicates if the Entity is hidden.
     * @return True if hidden, otherwise false.
     */
    [[nodiscard]] bool isHidden() const;

    /**
     * @brief Indicates if the Entity is dead.
     * @return True if dead, otherwise false.
     */
    [[nodiscard]] bool isDead() const;

    /**
     * @brief Handles the current status of the Entity.
     * @details This method is called during each tick to determine the
     * appropriate behavior for the Entity based on this current status.
     */
    virtual void handleStatus();

    /**
     * @brief Handle and update the Entity.
     */
    virtual void tick();

};

#endif //PACMAN_ENTITY_H
