#ifndef OBJECT_HPP_INCLUDE
#define OBJECT_HPP_INCLUDE

#include <utility>

class Object {
  private:
    std::pair<int, int> a;
    std::pair<int, int> b;

  public:
    virtual char show() const = 0;
    virtual std::pair<int, int> targetCell(const std::pair<int, int>& entry) const = 0;
};

#endif
