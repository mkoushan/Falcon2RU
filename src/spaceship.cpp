#include <iostream>
#include <stdexcept>
#include <string>

#include "spaceship.hpp"

void Spaceship::move(DIRECTION dir)
{
  // check if we can move to that direction
  if (this->location->getObject(dir) == nullptr) {
    throw std::invalid_argument(
        "moving towards "
        + std::to_string(dir)
        + " failed\n");
  }

  // moving towards the dir direction
  const auto& target = this->location->getObject(dir);
  this->location = target;
  this->energy -= 1;
  this->time += 5;


  // log
  std::string dir_str = dir == 0 ? "UP" : dir == 1 ? "RIGHT" : dir == 2 ? "DOWN" : dir == 3 ? "LEFT" : "WTF";
  std::string log_text = this->getTimeStr() + "\tMoved " + std::to_string(dir) + ",\tE:" + this->getEnergyStr();
  this->logs.push_back(log_text);

}

void Spaceship::orbit()
{
  if (this->location->getEnergyCost() != 12) {
      throw std::invalid_argument(
          "orbitting from "
          + this->location->getLocationStr()
          + " failed because there's no space object near the ship\n");
  }

  // orbiting through the space object
  const Object* target = this->location->targetCell();
  this->location = target;
  this->energy -= 12;
  this->time += 9;

  // log
  std::string log_text = this->getTimeStr() + "\tOrbited, " + "\tE:" + this->getEnergyStr();
  this->logs.push_back(log_text);

}

void Spaceship::teleport()
{
  if (this->location->show() != '4') {
      throw std::invalid_argument(
               "teleporting from "
               + this->location->getLocationStr()
               + " failed beacuse this cell is not a wormhole entry\n");
  }

  // teleporting
  const Object* target = this->location->targetCell();
  this->location = target;
  this->energy /= 2;

  // log
  std::string log_text = this->getTimeStr() + "\tTeleported," + "\tE:" + this->getEnergyStr();
  this->logs.push_back(log_text);

}

void Spaceship::ride()
{
  if (this->location->show() != '1') {
      throw std::invalid_argument(
                     "riding from "
                     + this->location->getLocationStr()
                     + " failed beacuse this cell is not a space current entry\n");
  }

  // riding
  const Object* target = this->location->targetCell();
  this->location = target;
  this->energy -= target->getEnergyCost();
  this->time += target->getTimeCost();

  // log
  std::string log_text = this->getTimeStr() + "\tRided, " + "\tE:" + this->getEnergyStr();
  this->logs.push_back(log_text);
}

const DIRECTION Spaceship::doSeeHome() const
{
  for (const auto& cell : this->location->getNeighbors()) {
      if (cell.second != nullptr && cell.second->isHome()) {
          return cell.first;
      }
  }
  return UNKNOWN;
}

void Spaceship::printLog() const
{
  for (const auto& log : this->logs) {
    std::clog << log << std::endl;
  }
}
