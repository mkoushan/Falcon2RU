#include <iostream>
#include <stdexcept>

#include "spaceship.hpp"

void Spaceship::move(DIRECTION dir)
{
  const auto& neighbors = this->location->getNeighbors();
  if (neighbors.at(dir) == nullptr) {
    throw;
  }
  const Object* target = neighbors.at(dir);
  this->energy -= 1;
  this->time += 5;

  std::string log_text = this->getTimeStr() + " Moved from " + this->location->getStr() + "to " + target->getStr() + ", E:" + this->getEnergyStr();
  this->logs.push_back(log_text);

  this->location = target;
}

void Spaceship::orbit()
{
  const Object* target = this->location->targetCell(this->location);
  this->energy -= 4;
  this->time += 3;

  std::string log_text = this->getTimeStr() + " Orbited from " + this->location->getStr() + " to " + target->getStr() + ", E:" + this->getEnergyStr();
  this->logs.push_back(log_text);

  this->location = target;
}

void Spaceship::teleport()
{
  const Object* target = this->location->targetCell(this->location);
  this->energy /= 2;

  std::string log_text = this->getTimeStr() + " Teleported from " + this->location->getStr() + " to " + target->getStr() + ", E:" + this->getEnergyStr();
  this->logs.push_back(log_text);

  this->location = target;
}

void Spaceship::ride()
{
  do {
    const Object* target = this->location->targetCell(this->location);
    this->energy -= 2;
    this->time += 1;

    std::string log_text = this->getTimeStr() + " Rided from " + this->location->getStr() + " to " + target->getStr() + ", E:" + this->getEnergyStr();
    this->logs.push_back(log_text);

    this->location = target;

  } while(this->location->show() != '1');
}

void Spaceship::printLog() const
{
  for (const auto& log : this->logs) {
    std::cout << log << std::endl;
  }
}
