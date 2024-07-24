#include "space.hpp"
#include <iostream>
void Space::buildMap(const std::vector<std::vector<char>>& raw_map)
{
  //std::clog << "INFO Entered build map\n";
  const unsigned int row = raw_map.size();
  const unsigned int col = raw_map.at(0).size();
  //std::clog << "INFO row = " << row << " col = " << col << '\n';
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

        case '2':
          this->buildPipe({i, j});
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
  //std::clog << "INFO leaving build map\n";
  this->connectCells();
}

void Space::buildCell(const Point& p, const bool is_home)
{
  this->map.at(p.first).at(p.second) = new Cell(p, is_home);
}

void Space::buildSpaceCurrent(const Point& p)
{
  this->map.at(p.first).at(p.second) = new Space_Current(p);
}

void Space::buildSpaceObject(const Point& p)
{
  this->map.at(p.first).at(p.second) = new Space_Object(p);
}

void Space::buildPipe(const Point& p)
{
  this->map.at(p.first).at(p.second) = new Pipe(p);
}

void Space::connectCells()
{
  //std::clog << "INFO entering connect cells\n";
  std::vector<Object*> wormholes;

  const unsigned int row = this->map.size();
  const unsigned int col = this->map.at(0).size();

  //std::clog << "INFO row = " << row << " col = " << col << '\n';

  /* 0 top, 1 right, 2 bottom, 3 left */
  std::vector<Object*> neighbors(4, nullptr);
  //std::clog << "INFO connecting side cells of the map\n";
  for (size_t i = 1; i < col - 1; ++i) {
    /* top side of the map */
    neighbors.at(0) = nullptr;
    neighbors.at(1) = this->map.at(0).at(i + 1);
    neighbors.at(2) = this->map.at(1).at(i);
    neighbors.at(3) = this->map.at(0).at(i - 1);

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
    //std::clog << "INFO top side of the map connected\n";

    /* right side of the map */
    neighbors.at(0) = this->map.at(i - 1).at(col - 1);
    neighbors.at(1) = nullptr;
    neighbors.at(2) = this->map.at(i + 1).at(col - 1);
    neighbors.at(3) = this->map.at(i).at(col - 2);

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
    //std::clog << "INFO right side of the map connected\n";

    /* bottom side of the map */
    neighbors.at(0) = this->map.at(row - 2).at(i);
    neighbors.at(1) = this->map.at(row - 1).at(i + 1);
    neighbors.at(2) = nullptr;
    neighbors.at(3) = this->map.at(row - 1).at(i - 1);

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

    //std::clog << "INFO bottom side of the map connected\n";
    /* left side of the map */
    neighbors.at(0) = this->map.at(i - 1).at(0);
    neighbors.at(1) = this->map.at(i).at(1);
    neighbors.at(2) = this->map.at(i + 1).at(0);
    neighbors.at(3) = nullptr;

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
    //std::clog << "INFO left side of the map connected\n";
  }

  //std::clog << "INFO all sides of the map succefully connected\n";
  /* 0 top, 1 right, 2 bottom, 3 left */
  /* connecting corners */
  //std::clog << "INFO connecting corners\n";
  /* top-left */
  //std::clog << "INFO connecting top-left corner\n";
  neighbors.at(0) = nullptr;
  neighbors.at(1) = this->map.at(0).at(1);
  neighbors.at(2) = this->map.at(1).at(0);
  neighbors.at(3) = nullptr;

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
  //std::clog << "INFO connecting top-right corner\n";
  neighbors.at(0) = nullptr;
  neighbors.at(1) = nullptr;
  neighbors.at(2) = this->map.at(1).at(col - 1);
  neighbors.at(3) = this->map.at(0).at(col - 2);

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
  //std::clog << "INFO connecting down-right corner\n";
  neighbors.at(0) = this->map.at(row - 2).at(col - 1);
  neighbors.at(1) = nullptr;
  neighbors.at(2) = nullptr;
  neighbors.at(3) = this->map.at(row - 1).at(col - 2);

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
  //std::clog << "INFO connecting down-left corner\n";
  neighbors.at(0) = this->map.at(row - 2).at(0);
  neighbors.at(1) = this->map.at(row - 1).at(1);
  neighbors.at(2) = nullptr;
  neighbors.at(3) = nullptr;

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
  //std::clog << "INFO all corners successfully connected\n";
  
  /* 0 top, 1 right, 2 bottom, 3 left */
  /* connecting mid-cells */
  //std::clog << "INFO connecting mid-cells\n";

  for (size_t i = 1; i < row - 1; ++i) {
    for (size_t j = 1; j < col - 1; ++j) {
      //std::clog << "INFO " << i << ' ' << j << '\n';
      neighbors.at(0) = this->map.at(i - 1).at(j);
      neighbors.at(1) = this->map.at(i).at(j + 1);
      neighbors.at(2) = this->map.at(i + 1).at(j);
      neighbors.at(3) = this->map.at(i).at(j - 1);

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
  //std::clog << "INFO all mid-cells successfully connected\n";

  /* connecting wormholes (if they exist) */
  if (wormholes.size() == 2) {
    wormholes.at(0)->setTarget(wormholes.at(1));
    wormholes.at(1)->setTarget(wormholes.at(0));
  }
}

void Space::connectSpaceCurrent(Object* start) 
{
  //std::clog << "INFO entered connectSpaceCurrent() with start cell: " << start->getLocation().first << ' ' << start->getLocation().second << '\n';
  do {
    for (const auto& obj : start->getNeighbors()) {
      if (obj->show() == '2' || obj->show() == '1') {
        start->setTarget(obj);
        start = obj;
      }
    }
  } while (start->show() != '1');
  //std::clog << "INFO leaving connectSpaceCurrent()\n";
}

void Space::connectSpaceObject(Object* start)
{
  // TODO
}
