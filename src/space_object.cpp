#include "space_object"

Space_Object::Space_Object(const std::vector<Object*> entries, const std::vector<Object*>& targets, const Point& location) {
   this->Object::setLocation(location);
   this->targets[entries[0]->getLocation()] = targets[0];
   this->targets[entries[1]->getLocation()] = targets[1];
}
