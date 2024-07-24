#ifndef SPACE_CURRENT_HPP_INCLUDED
#define SPACE_CURRENT_HPP_INCLUDED

#include "object.hpp"

class Space_Current : public Object {
  public:
    Space_Current(const Point& location) : Object(location) {}
    char show() const override{return '1';}
    const Object* targetCell(const Object* const entry) const override {return this->target;}
};

#endif // SPACE_CURRENT_HPP_INCLUDED
