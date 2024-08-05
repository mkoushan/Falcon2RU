#ifndef SPACE_HPP_INCLUDED
#define SPACE_HPP_INCLUDED

#include <vector>

#include "object.hpp"

class Spaceship;

class Space {
  private:
    std::vector<std::vector<Object*>> map;
    std::vector<std::vector<char>> raw_map;
    Spaceship* ship;

    void buildSpaceCurrent(const Point& p);
    void buildCell(const Point& p);
    void buildWormhole(Point const& p);

    void connectCells();
    void connectSpaceCurrent(Object* start);
    void connectSpaceObject(const Point& p);

  public:
    void buildMap(const std::vector<std::vector<char>>& raw_map);
    const Spaceship* getSpaceship() const {return this->ship;}
    const Object* const& getCell(const Point& p) const {return this->map.at(p.first).at(p.second);}
};

#endif // SPACE_HPP_INCLUDED
