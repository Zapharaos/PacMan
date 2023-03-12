//
// Created by matthieu on 07/02/2023.
//

#include <iostream>
#include "../../include/map/cell.h"
#include "../../include/utils/utils.h"

Cell::Cell() = default;

Cell::Cell(Position position, int size, CellType type,
           const optional<Entity> &entity) :
        position_(move(position)), size_(size), type_(type), entity_(entity)
{}

bool Cell::operator==(const Cell &rhs) const
{
    return position_ == rhs.position_;
}

bool Cell::operator!=(const Cell &rhs) const
{
    return !(rhs == *this);
}

CellType Cell::getType() const
{
    return type_;
}

const optional<Entity> &Cell::getEntity() const
{
    return entity_;
}

void Cell::setEntity(const Entity &entity)
{
    entity_ = entity;
}

bool Cell::isNeighbor(const Cell &cell) const
{
    return position_.isNeighbor(cell.position_);
}

bool Cell::equalsPositionScaled(Position position) const
{
    return position == getPositionScaled();
}

Position Cell::getPositionScaled() const
{
    return position_.getPositionScaled(size_);
}

void Cell::setEnabled(bool enabled)
{
    entity_->setEnabled(enabled);
}

void Cell::print() const
{
    position_.print();
    position_.getPositionScaled(size_).print();
    cout << static_cast<std::underlying_type<CellType>::type>(type_) << endl;
    entity_->print();
}
