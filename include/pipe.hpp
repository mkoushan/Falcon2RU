#ifndef PIPE_HPP_INCLUDED
#define PIPE_HPP_INCLUDED

#include "object.hpp"

class Pipe : public Object {
  public:
    Pipe(const Point& location) : Object(location) {}
    char show() const override {return '2';}
    const Object* targetCell(const Object* const entry) const override {return this->target;}
};

#endif // PIPE_HPP_INCLUDED
