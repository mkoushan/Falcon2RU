#ifndef OBJECT_HPP_INCLUDE
#define OBJECT_HPP_INCLUDE

#include <utility>
#include <vector>
#include <string>

typedef std::pair<unsigned int, unsigned int> Point;

class Object {
  protected:
    Point location;
    std::vector<Object*> neighbors;
    const Object* target;
  public:
    Object(const Point& p) : location(p) {}

    virtual char show() const = 0;
    virtual const Object* targetCell(const Object* const entry) const = 0;

    virtual void setTarget(Object* target) { this->target = target; }
    void setNeighbors(const std::vector<Object*>& neighbors) {this->neighbors = neighbors;}

    const std::vector<Object*>& getNeighbors() const {return this->neighbors;}
    const Point getLocation() const {return this->location;}
    const std::string getStr() const { return "(" + std::to_string(this->location.first) + "," + std::to_string(this->location.second) + ")"; }
};

#endif
