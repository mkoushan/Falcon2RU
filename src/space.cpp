#include "space.hpp"

void Space::buildMap(const std::vector<std::vector<char>>& raw_map)
{
  const unsigned int row = raw_map.size();
  const unsigned int col = raw_map.at(0).size();
 
  this->map.assign(row, std::vector<Object*>(col, nullptr));

  std::vector<std::vector<bool>> visited(row, std::vector<bool>(col, false));

  std::vector<Point> wormholes;

  for (size_t i = 0; i < row; ++i) {
    for (size_t j = 0; j < col; ++j) {
      switch(raw_map.at(i).at(j)) {
        case '0':
          this->buildCell({i, j});
          break;

        case '1':
          this->buildSpaceCurrent({i, j});
          break;

        case '3':
          this->buildSpaceObject({i, j});
          break;

        case '4':
          wormholes.push_back({i, j});
          break;

        case '5':
          this->buildCell({i, j}, true);
          break;

        default: 
          break;
      }
    }
  }

  Point a = wormholes.at(0);
  Point b = wormholes.at(1);
  this->map.at(a.first).at(a.second) = new Wormhole (a);
  this->map.at(b.first).at(b.second) = new Wormhole (b);
}

void Space::buildCell(const Point& p, const bool is_home)
{
  this->map.at(p.first).at(p.second) = new Cell(p, is_home);
}

void Space::buildSpaceCurrent(const Point& p)
{
  // TODO
  this->map.at(p.first).at(p.second) = new Space_Current(p);
}

void Space::buildSpaceObject(const Point& p)
{
  // TODO
}
