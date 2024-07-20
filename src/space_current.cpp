#include "space_current.hpp"

Space_Current::Space_Current(const std::vector<Object*>& neighbors, const Object*& target) {
   this->Object::neighbors = neighbors;
   this->target = target;
}
