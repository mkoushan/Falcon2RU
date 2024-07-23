#ifndef SPACE_CURRENT_HPP_INCLUDED
#define SPACE_CURRENT_HPP_INCLUDED

#include "object.hpp"

class Space_Current : public Object {
  private:
    const Object* target;

  public:
    Space_Current(const Point& location) : Object(location) {}
    void setTarget(const Object*& target) {this->target = target;}
    char show() const override{return '1';}
    const Object* targetCell(const Object* const entry) const override {return this->target;}
    const int getEnergyCost() const override {return 2;}
    const int getTimeCost() const override {return 1;}
};

#endif // SPACE_CURRENT_HPP_INCLUDED
