#ifndef SPACE_OBJECT_INCLUDED
#define SPACE_OBJECT_INCLUDED

#include "object.hpp"
#include <vector>
#include <map>

class Space_Object: Object {
private:
   std::map<Point,Object*> targets;
public:
   Space_Object(const std::vector<Object*> entries, const std::vector<Object*>& targets, const Point& location);
   char show() const override{return '3';}
   const Object* targetCell(const Object* const entry) const override {return this->targets[entry->getLocation()];}
   const int getEnergyCost() const override {return 4;}
   const int getTimeCost() const override {return 3;}
};

#endif // SPACE_OBJECT_INCLUDED
