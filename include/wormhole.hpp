#ifndef WORMHOLE_HPP_INCLUDED
#define WORMHOLE_HPP_INCLUDED

#include "object.hpp"

class Wormhole : public Object {
  public:
    Wormhole(const Point& location) : Object(location) {}
    char show() const override{return '4';}
    const Object* targetCell(const Object* const entry) const override {return this->target;}
};

#endif // WORMHOLE_HPP_INCLUDED
