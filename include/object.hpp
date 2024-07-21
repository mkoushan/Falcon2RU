#ifndef OBJECT_HPP_INCLUDE
#define OBJECT_HPP_INCLUDE

#include <utility>
#include <vector>

typedef std::pair<int,int> Point;

class Object {
protected:
   std::vector<Object*> neighbors;
public:
   virtual char show() const = 0;
   virtual const Object* targetCell(const Object* const entry = nullptr) const {return nullptr;}
   virtual const int getEnergyCost() const {return 1;}
   virtual const int getTimeCost() const {return 5;}
   const std::vector<Object*>& getNeighbors() const {return this->neighbors;}
};

#endif
