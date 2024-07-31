#include <iostream>
#include <stdexcept>

#include "spaceship.hpp"

void Spaceship::move(DIRECTION dir)
{
  // check if we can move to that direction
  if (this->location->getObject(dir) == nullptr) {
    throw std::invalid_argument(
        "moving from "
        + this->location->getLocationStr()
        + " to direction "
        + std::to_string(dir)
        + " failed\n");
  }
  // log
  const auto& target = this->location->getObject(dir);
  std::string log_text = this->getTimeStr() + " Moved from " + this->location->getLocationStr() + "to " + target->getLocationStr() + ", E:" + this->getEnergyStr();
  this->logs.push_back(log_text);

  // finally moving towards the dir direction
  this->location = target;
  this->energy -= 1;
  this->time += 5;
}

void Spaceship::orbit()
{
  if (this->location->getEnergyCost() != 12) {
      throw std::invalid_argument(
          "orbitting from "
          + this->location->getLocationStr()
          + " failed because there's no space object near the ship\n");
  }

  // log
  const Object* target = this->location->targetCell();
  std::string log_text = this->getTimeStr() + " Orbited from " + this->location->getLocationStr() + " to " + target->getLocationStr() + ", E:" + this->getEnergyStr();
  this->logs.push_back(log_text);

  // orbiting through the space object
  this->location = target;
  this->energy -= 12;
  this->time += 9;
}

void Spaceship::teleport()
{
  if (this->location->show() != '4') {
      throw std::invalid_argument(
               "teleporting from "
               + this->location->getLocationStr()
               + " failed beacuse this cell is not a wormhole entry\n");
  }

 // log
  const Object* target = this->location->targetCell();
  std::string log_text = this->getTimeStr() + " Teleported from " + this->location->getLocationStr() + " to " + target->getLocationStr() + ", E:" + this->getEnergyStr();
  this->logs.push_back(log_text);

  // teleporting
  this->location = target;
  this->energy /= 2;
}

void Spaceship::ride()
{
  if (this->location->show() != '1') {
      throw std::invalid_argument(
                     "riding from "
                     + this->location->getLocationStr()
                     + " failed beacuse this cell is not a space current entry\n");
  }

  // log
  const Object* target = this->location->targetCell();
  std::string log_text = this->getTimeStr() + " Rided from " + this->location->getLocationStr() + " to " + target->getLocationStr() + ", E:" + this->getEnergyStr();
  this->logs.push_back(log_text);

  // riding
  this->location = target;
  this->energy -= target->getEnergyCost();
  this->time += target->getTimeCost();
}

const DIRECTION Spaceship::doSeeHome() const
{
  for (const auto& cell : this->location->getNeighbors()) {
      if (cell.second != nullptr && cell.second->isHome()) {
          std::clog << 1;
          return cell.first;
      }
  }
  return UNKNOWN;
}

void Spaceship::printLog() const
{
  for (const auto& log : this->logs) {
    std::cout << log << std::endl;
  }
}
