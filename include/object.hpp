#ifndef OBJECT_HPP_INCLUDE
#define OBJECT_HPP_INCLUDE

#include <utility>

typedef std::pair<int,int> Point;

class Object {
  public:
    virtual char show() const = 0;
    virtual std::pair<int, int> targetCell(const std::pair<int, int>& entry) const = 0;
};

#endif
