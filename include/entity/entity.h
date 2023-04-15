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
#include "../config/config.h"

/**
 * @brief An object located on the map.
 */
class Entity
{

private:

    /*
     * @brief EntityStatus enumeration.
     * Defines entity visibility status.
     */
    enum class EntityStatus {
        kVisible, /* Entity is visible. */
        kHidden, /* Entity is hidden. */
        kDead, /* Entity is dead. */
        kFrozen /* Entity is frozen. */
    };

    /** Raw position. */
    Position position_{};

    /** Image when displayed. */
    Sprite sprite_{};

    int size_{config::dimensions::kMovingEntitySize};

    /** If the entity is active. */
    bool enabled_ = false;

    /** Points earned when entity is eaten. */
    unsigned long points_{};

    /** Entity status. */
    EntityStatus status_ {EntityStatus::kVisible};

    /** Counts a number of frames. */
    Counter counter_ {};

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

    int getSize() const;

    /**
     * @brief Getter for the sprite used to display the entity.
     * @return The new sprite used to display the entity.
     */
    [[nodiscard]] const Sprite &getSprite() const;

    /**
     * @brief Setter for the sprite used to display the entity.
     * @param sprite The new sprite used to display the entity.
     */
    void setSprite(const Sprite &sprite);

    /**
     * @brief Getter for the number of points earned when the entity is eaten.
     * @return The number of points earned when the entity is eaten.
     */
    [[nodiscard]] unsigned long getPoints() const;

    /**
     * @brief Setter for the number of points earned when the entity is eaten.
     * @param points The new number of points earned when the entity is eaten.
     */
    void setPoints(unsigned long points);

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
     * @brief Count for a certain amount of frames.
     * @param frames Amount of frames.
     * @see Counter::start()
     */
    void count(long frames);

    /**
     * @brief Indicates if the counter is active (i.e. frames are being counted).
     * @return True if active, else false.
     */
    [[nodiscard]] bool isCounterActive() const;

    /**
     * @brief Increments the counter.
     * @see Counter::increment()
     */
    void counterIncrement();

    /**
     * @brief Hide entity.
     */
    void hide();

    /**
     * @brief Show entity.
     */
    void show();

    /**
     * @brief Kill entity.
     */
    virtual void kill();

    /**
     * @brief Freeze entity.
     */
    void freeze();

    /**
     * @brief Indicates if the entity is visible.
     * @return bool True if visible, else false.
     */
    [[nodiscard]] bool isVisible() const;

    /**
     * @brief Indicates if the entity is hidden.
     * @return bool True if hidden, else false.
     */
    [[nodiscard]] bool isHidden() const;

    /**
     * @brief Indicates if the entity is dead.
     * @return bool True if dead, else false.
     */
    [[nodiscard]] bool isDead() const;

    /**
     * @brief Toggles the entity status and its visibility according to the counter member.
     * @return bool True if visible, false if hidden.
     */
    bool tickVisibility();

};

#endif //PEC_MEN_ENTITY_H
