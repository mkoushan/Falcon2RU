
#ifndef PIPE_HPP_INCLUDED
#define PIPE_HPP_INCLUDED

#include "object.hpp"

class Pipe: Object {
private:
   const Object* target;
public:
   Pipe(const Object*& target) : target(target) {}
   char show() const override{return '2';}
   const Object* targetCell(const Object* const entry) const override {return this->target;}
   const int getEnergyCost() const override {return 2;}
   const int getTimeCost() const override {return 1;}
};

#endif // PIPE_HPP_INCLUDED
