//
// Created by matthieu on 07/02/2023.
//

#include "../../include/map/cell.h"

#include <iostream>
#include <utility>

#include "../../include/utils/utils.h"

Cell::Cell() = default;

Cell::Cell(Position position, int size, const CellType &type,
           std::shared_ptr<Entity> entity) :
        position_(std::move(position)), size_(size), type_(type), entity_(std::move(entity))
{}

bool Cell::operator==(const Cell &rhs) const
{
    return position_ == rhs.position_;
}

bool Cell::operator!=(const Cell &rhs) const
{
    return !(rhs == *this);
}

const CellType &Cell::getType() const
{
    return type_;
}

const std::shared_ptr<Entity> &Cell::getEntity() const
{
    return entity_;
}

bool Cell::isNeighbor(const Cell &cell) const
{
    return position_.isNeighbor(cell.position_);
}

bool Cell::equalsPositionScaled(const Position &position) const
{
    return position == getPositionScaled();
}

Position Cell::getPositionScaled() const
{
    return position_.getPositionScaled(size_);
}

void Cell::print() const
{
    position_.print();
    position_.getPositionScaled(size_).print();
    std::cout << static_cast<std::underlying_type<CellType>::type>(type_) << std::endl;
    entity_->print();
}
