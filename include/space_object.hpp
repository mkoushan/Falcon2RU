#ifndef SPACE_OBJECT_INCLUDED
#define SPACE_OBJECT_INCLUDED

#include "object.hpp"
#include <vector>
#include <map>

class Space_Object : public Object {
  private:
    std::map<Point,Object*> targets;

  public:
    Space_Object(const Point& location) : Object(location) {}
    char show() const override {return '3';}
    void setTarget(const Object*& target); /* TODO */
    const Object* targetCell(const Object* const entry) const override {return this->targets.at(entry->getLocation());}
    const int getEnergyCost() const override {return 4;}
    const int getTimeCost() const override {return 3;}
};

#endif // SPACE_OBJECT_INCLUDED
