#ifndef WORMHOLE_HPP_INCLUDED
#define WORMHOLE_HPP_INCLUDED

#include "object.hpp"

class Wormhole : public Object {
  private:
    const Object* target;

  public:
    Wormhole(const Point& location) : Object(location) {}
    void setTarget(const Object*& target) {this->target = target;}
    char show() const override{return '4';}
    const Object* targetCell(const Object* const entry) const override {return this->target;}
    const int getEnergyCost() const override {return -11;} /* this will be handled in coontrol class */
    const int getTimeCost() const override {return 0;}
};

#endif // WORMHOLE_HPP_INCLUDED
