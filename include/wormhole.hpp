#ifndef WORMHOLE_HPP_INCLUDED
#define WORMHOLE_HPP_INCLUDED

#include "object.hpp"
// TODO
// #include "space_ship.hpp"

class Wormhole: Object {
private:
   const Object* target;
public:
   Pipe(const Object*& target) : target(target) {}
   char show() const override{return '4';}
   const Object* targetCell(const Object* const entry) const override {return this->target;}
   const int getEnergyCost() const override {return 2;} // TODO
   const int getTimeCost() const override {return 0;}
};

#endif // WORMHOLE_HPP_INCLUDED
