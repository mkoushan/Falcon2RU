#ifndef SPACE_HPP_INCLUDED
#define SPACE_HPP_INCLUDED

#include "spaceship.hpp"
#include "object.hpp"

#include <vector>

class Space {
   private:
      std::vector<std::vector<Object*>> map;
      Spaceship* ship;
   public:
      void setMap(const unsigned int& row, const unsigned int& col);
      const char getCell(const unsigned int& x, const unsigned int& y) const {
         return this->map.at(x).at(y)->show();}
};

#endif // SPACE_HPP_INCLUDED
