#include "space.hpp"
#include "object.hpp"

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
  const auto& a_ptr = this->map.at(a.first).at(a.second) = new Object(a, '4');
  const auto& b_ptr = this->map.at(b.first).at(b.second) = new Object(b, '4');

  a_ptr->setEnergyCost(-11);
  a_ptr->setTimeCost(0);
  a_ptr->setTarget(b_ptr);

  b_ptr->setEnergyCost(-11);
  b_ptr->setTimeCost(0);
  b_ptr->setTarget(a_ptr);
}

void Space::buildCell(const Point& p, const bool is_home)
{
  this->map.at(p.first).at(p.second) = new Object(p, '0', is_home);
}

void Space::buildSpaceCurrent(const Point& p)
{
  this->map.at(p.first).at(p.second) = new Object(p, '1');
}

void Space::buildSpaceObject(const Point& p)
{
  this->map.at(p.first).at(p.second) = new Object(p, '3');
}

void Space::connectCells()
{
  std::vector<Object*> wormholes;

  const unsigned int row = this->map.size();
  const unsigned int col = this->map.at(0).size();

  std::map<DIRECTION, Object*> neighbors;

  for (size_t i = 1; i < col - 1; ++i) {
    /* top side of the map */
    neighbors.at(UP)    = nullptr;
    neighbors.at(RIGHT) = this->map.at(0).at(i + 1);
    neighbors.at(LEFT)  = this->map.at(1).at(i);
    neighbors.at(DOWN)  = this->map.at(0).at(i - 1);

    switch (this->map.at(0).at(i)->show()) {
      case '4':
        wormholes.push_back(this->map.at(0).at(i));
        this->map.at(0).at(i)->setNeighbors(neighbors);
        break;

      case '1':
        connectSpaceCurrent(this->map.at(0).at(i));
        this->map.at(0).at(i)->setNeighbors(neighbors);
        break;

      case '0':
        this->map.at(0).at(i)->setNeighbors(neighbors);
        break;
    }

    /* right side of the map */
    neighbors.at(UP)    = this->map.at(i - 1).at(col - 1);
    neighbors.at(RIGHT) = nullptr;
    neighbors.at(DOWN)  = this->map.at(i + 1).at(col - 1);
    neighbors.at(LEFT)  = this->map.at(i).at(col - 2);

    switch (this->map.at(i).at(col - 1)->show()) {
      case '4':
        wormholes.push_back(this->map.at(i).at(col - 1));
        this->map.at(i).at(col - 1)->setNeighbors(neighbors);
        break;

      case '1':
        connectSpaceCurrent(this->map.at(i).at(col - 1));
        this->map.at(i).at(col - 1)->setNeighbors(neighbors);
        break;

      case '0':
        this->map.at(i).at(col - 1)->setNeighbors(neighbors);
        break;
    }

    /* bottom side of the map */
    neighbors.at(UP)    = this->map.at(row - 2).at(i);
    neighbors.at(RIGHT) = this->map.at(row - 1).at(i + 1);
    neighbors.at(DOWN)  = nullptr;
    neighbors.at(LEFT)  = this->map.at(row - 1).at(i - 1);

    switch (this->map.at(row - 1).at(i)->show()) {
      case '4':
        wormholes.push_back(this->map.at(row - 1).at(i));
        this->map.at(row - 1).at(i)->setNeighbors(neighbors);
        break;

      case '1':
        connectSpaceCurrent(this->map.at(row - 1).at(i));
        this->map.at(row - 1).at(i)->setNeighbors(neighbors);
        break;

      case '0':
        this->map.at(row - 1).at(i)->setNeighbors(neighbors);
        break;
    }

    /* left side of the map */
    neighbors.at(UP)    = this->map.at(i - 1).at(0);
    neighbors.at(RIGHT) = this->map.at(i).at(1);
    neighbors.at(DOWN)  = this->map.at(i + 1).at(0);
    neighbors.at(LEFT)  = nullptr;

    switch (this->map.at(i).at(0)->show()) {
      case '4':
        wormholes.push_back(this->map.at(i).at(0));
        this->map.at(i).at(0)->setNeighbors(neighbors);
        break;

      case '1':
        connectSpaceCurrent(this->map.at(i).at(0));
        this->map.at(i).at(0)->setNeighbors(neighbors);
        break;

      case '0':
        this->map.at(i).at(0)->setNeighbors(neighbors);
        break;
    }
  }

  /* connecting corners */
  /* top-left */
  neighbors.at(UP)      = nullptr;
  neighbors.at(RIGHT)   = this->map.at(0).at(1);
  neighbors.at(DOWN)    = this->map.at(1).at(0);
  neighbors.at(LEFT)    = nullptr;

  switch (this->map.at(0).at(0)->show()) {
    case '4':
      wormholes.push_back(this->map.at(0).at(0));
      this->map.at(0).at(0)->setNeighbors(neighbors);
      break;

    case '1':
      connectSpaceCurrent(this->map.at(0).at(0));
      this->map.at(0).at(0)->setNeighbors(neighbors);
      break;

    case '0':
      this->map.at(0).at(0)->setNeighbors(neighbors);
      break;
  }

  /* top-right */
  neighbors.at(UP)      = nullptr;
  neighbors.at(RIGHT)   = nullptr;
  neighbors.at(DOWN)    = this->map.at(1).at(col - 1);
  neighbors.at(LEFT)    = this->map.at(0).at(col - 2);

  switch (this->map.at(0).at(col - 1)->show()) {
    case '4':
      wormholes.push_back(this->map.at(0).at(col - 1));
      this->map.at(0).at(col - 1)->setNeighbors(neighbors);
      break;

    case '1':
      connectSpaceCurrent(this->map.at(0).at(col - 1));
      this->map.at(0).at(col - 1)->setNeighbors(neighbors);
      break;

    case '0':
      this->map.at(0).at(col - 1)->setNeighbors(neighbors);
      break;
  }

  /* down-right */
  neighbors.at(UP)      = this->map.at(row - 2).at(col - 1);
  neighbors.at(RIGHT)   = nullptr;
  neighbors.at(DOWN)    = nullptr;
  neighbors.at(LEFT)    = this->map.at(row - 1).at(col - 2);

  switch (this->map.at(row - 1).at(col - 1)->show()) {
    case '4':
      wormholes.push_back(this->map.at(row - 1).at(col - 1));
      this->map.at(row - 1).at(col - 1)->setNeighbors(neighbors);
      break;

    case '1':
      connectSpaceCurrent(this->map.at(row - 1).at(col - 1));
      this->map.at(row - 1).at(col - 1)->setNeighbors(neighbors);
      break;

    case '0':
      this->map.at(row - 1).at(col - 1)->setNeighbors(neighbors);
      break;
  }

  /* down-left*/
  neighbors.at(UP)      = this->map.at(row - 2).at(0);
  neighbors.at(RIGHT)   = this->map.at(row - 1).at(1);
  neighbors.at(DOWN)    = nullptr;
  neighbors.at(LEFT)    = nullptr;

  switch (this->map.at(row - 1).at(0)->show()) {
    case '4':
      wormholes.push_back(this->map.at(row - 1).at(0));
      this->map.at(row - 1).at(0)->setNeighbors(neighbors);
      break;

    case '1':
      connectSpaceCurrent(this->map.at(row - 1).at(0));
      this->map.at(row - 1).at(0)->setNeighbors(neighbors);
      break;

    case '0':
      this->map.at(row - 1).at(0)->setNeighbors(neighbors);
      break;
  }

  /* connecting mid-cells */

  for (size_t i = 1; i < row - 1; ++i) {
    for (size_t j = 1; j < col - 1; ++j) {
      neighbors.at(UP)      = this->map.at(i - 1).at(j);
      neighbors.at(RIGHT)   = this->map.at(i).at(j + 1);
      neighbors.at(DOWN)    = this->map.at(i + 1).at(j);
      neighbors.at(LEFT)    = this->map.at(i).at(j - 1);

      switch (this->map.at(i).at(j)->show()) {
        case '0': /* empty cell */
        case '5':
          this->map.at(i).at(j)->setNeighbors(neighbors);
          break;

        case '1': /* side of space current */
          this->connectSpaceCurrent(this->map.at(i).at(j));
          this->map.at(i).at(j)->setNeighbors(neighbors);
          break;

        case '3': /* side of space object */
          this->connectSpaceObject(this->map.at(i).at(j));
          break;

        case '4': /* side of wormhole */
          wormholes.push_back(this->map.at(i).at(j));
          this->map.at(i).at(j)->setNeighbors(neighbors);
          break;

        default:
          break;
      }
    }
  }

  /* connecting wormholes (if they exist) */
  if (wormholes.size() == 2) {
    wormholes.at(0)->setTarget(wormholes.at(1));
    wormholes.at(1)->setTarget(wormholes.at(0));
  }
}

void Space::connectSpaceCurrent(Object* start)
{
    unsigned int total_energy_cost = 2;
    unsigned int total_time_cost   = 1;

    const Point& begin = start->getLocation();
    Point last = begin;
    Point current;

    for (const auto& cell : start->getNeighbors()) {
        if (cell.second == nullptr) {
            current = cell.second->getLocation();
            break;
        }
    }

    do {
        total_energy_cost += 2;
        total_time_cost   += 1;

        if ( 0 <= current.first - 1) {
            if (this->raw_map.at(current.first - 1).at(current.second) == '2') {
                last = current;
                current.first--;
            }
        } else if (current.first + 1 <= this->raw_map.size()) {
            if (this->raw_map.at(current.first + 1).at(current.second) == '2') {
                last = current;
                current.first++;
            }
        } else if (0 <= current.second - 1) {
            if (this->raw_map.at(current.first).at(current.second - 1) == '2') {
                last = current;
                current.second--;
            }
        } else if (current.second + 1<=this->raw_map.at(0).size()) {
            if (this->raw_map.at(current.first).at(current.second + 1) == '2') {
                last = current;
                current.second++;
            }
        }
    } while (last != current);

    auto& end = this->map.at(current.first).at(current.second);
    end->setTarget(start);
    end->setEnergyCost(total_energy_cost);
    end->setTimeCost(total_time_cost);
}

void Space::connectSpaceObject(Object* start)
{
  // TODO
}
