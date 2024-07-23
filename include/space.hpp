#ifndef SPACE_HPP_INCLUDED
#define SPACE_HPP_INCLUDED

#include <vector>

#include "pipe.hpp"
#include "space_current.hpp"
#include "space_object.hpp"
#include "wormhole.hpp"
#include "object.hpp"
#include "cell.hpp"

class Spaceship;

class Space {
  private:
    std::vector<std::vector<Object*>> map;
    std::vector<std::vector<char>> raw_map;
    Spaceship* ship;

    void buildSpaceCurrent(const Point& p);
    void buildSpaceObject(const Point& p);
    void buildCell(const Point& p, const bool is_home = false);

  public:
    void buildMap(const std::vector<std::vector<char>>& raw_map);
    const Spaceship* getSpaceship() const {return this->ship;}
    const Object* getCell(const Point& p) const {return this->map.at(p.first).at(p.second);}
};

#endif // SPACE_HPP_INCLUDED
