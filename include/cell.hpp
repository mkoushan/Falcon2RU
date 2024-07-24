#ifndef CELL_HPP_INCLUDED
#define CELL_HPP_INCLUDED

#include "object.hpp"

class Cell : public Object {
  private:
    bool is_home;
  public:
    Cell(const Point& location, const bool is_home = false) : Object(location), is_home(is_home) {}
    char show() const override {return is_home ? '5' : '0'; }
    const Object* targetCell(const Object* const entry) const override {return nullptr;}
};

#endif // PIPE_HPP_INCLUDED
