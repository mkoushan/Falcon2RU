#include "space_current.hpp"

Space_Current::Space_Current(const std::vector<Object*>& neighbors, const Object*& target, const Point& location) {
   this->Object::neighbors = neighbors;
   this->target = target;
   this->Object::setLocation(location);
}
