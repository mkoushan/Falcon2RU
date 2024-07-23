#ifndef OBJECT_HPP_INCLUDE
#define OBJECT_HPP_INCLUDE

#include <utility>
#include <vector>

typedef std::pair<unsigned int, unsigned int> Point;

class Object {
  protected:
    Point location;
    std::vector<Object*> neighbors;

  public:
    Object(const Point& p) : location(p) {}
    virtual char show() const = 0;
    virtual const Object* targetCell(const Object* const entry) const = 0;
    virtual const int getEnergyCost() const {return 1;}
    virtual const int getTimeCost() const {return 5;}
    void setNeighbors(const std::vector<Object*>& neighbors) {this->neighbors = neighbors;}
    const std::vector<Object*>& getNeighbors() const {return this->neighbors;}
    const Point getLocation() const {return this->location;}
};

#endif
