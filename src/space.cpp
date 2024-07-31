#include "space.hpp"
#include "object.hpp"

void Space::buildMap(const std::vector<std::vector<char>>& raw_map)
{
  this->raw_map = raw_map;

  const unsigned int row = raw_map.size();
  const unsigned int col = raw_map.at(0).size();

  this->map.assign(row, std::vector<Object*>(col, nullptr));

  for (size_t i = 0; i < row; ++i) {
    for (size_t j = 0; j < col; ++j) {
      switch(raw_map.at(i).at(j)) {
        case '0':
          this->buildCell({i, j});
          break;

        case '1':
          this->buildSpaceCurrent({i, j});
          break;

        case '2':
            this->map.at(i).at(j) = new Object({i, j}, '2');
        break;

        case '3':
          this->buildSpaceObject({i, j});
          break;

        case '4':
          this->buildWormhole({i, j});
          break;

        case '5':
          this->buildCell({i, j});
          break;

        default:
          break;
      }
    }
  }

  this->connectCells();
}

void Space::buildCell(const Point& p)
{
  this->map.at(p.first).at(p.second) = new Object(p, this->raw_map.at(p.first).at(p.second));
}

void Space::buildSpaceCurrent(const Point& p)
{
  this->map.at(p.first).at(p.second) = new Object(p, '1');
}

void Space::buildSpaceObject(const Point& p)
{
  this->map.at(p.first).at(p.second) = new Object(p, '3');
}

void Space::buildWormhole(Point const& p)
{
    this->map.at(p.first).at(p.second) = new Object(p, '4');
}

#include <iostream>
void Space::connectCells()
{
  std::vector<Object*> wormholes;

  const unsigned int row = this->map.size();
  const unsigned int col = this->map.at(0).size();

  std::map<DIRECTION, Object*> neighbors;

  for (size_t i = 1; i < col - 1; ++i) {
    /* top side of the map */
    neighbors[UP]    = nullptr;
    neighbors[RIGHT] = this->map.at(0).at(i + 1);
    neighbors[LEFT]  = this->map.at(1).at(i);
    neighbors[DOWN]  = this->map.at(0).at(i - 1);

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
    neighbors[UP]    = this->map.at(i - 1).at(col - 1);
    neighbors[RIGHT] = nullptr;
    neighbors[DOWN]  = this->map.at(i + 1).at(col - 1);
    neighbors[LEFT]  = this->map.at(i).at(col - 2);

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
    neighbors[UP]    = this->map.at(row - 2).at(i);
    neighbors[RIGHT] = this->map.at(row - 1).at(i + 1);
    neighbors[DOWN]  = nullptr;
    neighbors[LEFT]  = this->map.at(row - 1).at(i - 1);

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
    neighbors[UP]    = this->map.at(i - 1).at(0);
    neighbors[RIGHT] = this->map.at(i).at(1);
    neighbors[DOWN]  = this->map.at(i + 1).at(0);
    neighbors[LEFT]  = nullptr;

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
  neighbors[UP]      = nullptr;
  neighbors[RIGHT]   = this->map.at(0).at(1);
  neighbors[DOWN]    = this->map.at(1).at(0);
  neighbors[LEFT]    = nullptr;

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
  neighbors[UP]      = nullptr;
  neighbors[RIGHT]   = nullptr;
  neighbors[DOWN]    = this->map.at(1).at(col - 1);
  neighbors[LEFT]    = this->map.at(0).at(col - 2);

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
  neighbors[UP]      = this->map.at(row - 2).at(col - 1);
  neighbors[RIGHT]   = nullptr;
  neighbors[DOWN]    = nullptr;
  neighbors[LEFT]    = this->map.at(row - 1).at(col - 2);

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
  neighbors[UP]      = this->map.at(row - 2).at(0);
  neighbors[RIGHT]   = this->map.at(row - 1).at(1);
  neighbors[DOWN]    = nullptr;
  neighbors[LEFT]    = nullptr;

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
      neighbors[UP]      = this->map.at(i - 1).at(j);
      neighbors[RIGHT]   = this->map.at(i).at(j + 1);
      neighbors[DOWN]    = this->map.at(i + 1).at(j);
      neighbors[LEFT]    = this->map.at(i).at(j - 1);

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
      wormholes.at(0)->setEnergyCost(-11);
      wormholes.at(0)->setTimeCost(0);
      wormholes.at(0)->setTarget(wormholes.at(1));

      wormholes.at(1)->setEnergyCost(-11);
      wormholes.at(1)->setTimeCost(0);
      wormholes.at(1)->setTarget(wormholes.at(0));
  }
}

void Space::connectSpaceCurrent(Object* start)
{
    std::clog << '\n';
    for (const auto& i : this->map) {
        for (const auto& j : i) {
            std::clog << j->show();
        }
        std::clog << std::endl;
    }
    std::clog << '\n';
    unsigned int total_energy_cost = 2;
    unsigned int total_time_cost   = 1;

    const Point& begin = start->getLocation();
    Point current = begin;
    DIRECTION flag;

    if (1 <= begin.first && this->raw_map.at(begin.first - 1).at(begin.second) == '2') {
        current.first--;
        flag = DOWN;
    } else if (begin.first < this->raw_map.size() && this->raw_map.at(begin.first + 1).at(begin.second) == '2') {
        current.first++;
        flag = UP;
    } else if (1 <= begin.second && this->raw_map.at(begin.first).at(begin.second - 1) == '2') {
        current.second--;
        flag = RIGHT;
    } else if (begin.second < this->raw_map.at(0).size() && this->raw_map.at(begin.first).at(begin.second + 1) == '2') {
        current.second++;
        flag = LEFT;
    }

    do {
        total_energy_cost += 2;
        total_time_cost   += 1;

        if (flag != UP && 1 <= current.first) {
            if (this->raw_map.at(current.first - 1).at(current.second) == '2'
                && this->raw_map.at(current.first - 1).at(current.second) == '1') {
                current.first--;
                flag = DOWN;
            }
        } else if (flag != DOWN && current.first + 1 <= this->raw_map.size()) {
            if (this->raw_map.at(current.first + 1).at(current.second) == '2'
                && this->raw_map.at(current.first + 1).at(current.second) == '1') {
                current.first++;
                flag = UP;
            }
        } else if (flag != LEFT && 1 <= current.second) {
            if (this->raw_map.at(current.first).at(current.second - 1) == '2'
                && this->raw_map.at(current.first).at(current.second - 1) == '1') {
                current.second--;
                flag = RIGHT;
            }
        } else if (flag != RIGHT && current.second + 1 <= this->raw_map.at(0).size()) {
            if (this->raw_map.at(current.first).at(current.second + 1) == '2'
                && this->raw_map.at(current.first).at(current.second + 1) == '1') {
                current.second++;
                flag = LEFT;
            }
        }
    } while (this->raw_map.at(current.first).at(current.second) == '2');

    auto& end = this->map.at(current.first).at(current.second);
    end->setTarget(start);
    end->setEnergyCost(total_energy_cost);
    end->setTimeCost(total_time_cost);
    std::clog << 1;
}

void Space::connectSpaceObject(Object* start)
{
  // TODO
}
