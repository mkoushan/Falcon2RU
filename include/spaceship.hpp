#ifndef SPACESHIP_HPP_INCLUDED
#define SPACESHIP_HPP_INCLUDED

#include "object.hpp"
#include "space.hpp"

class Spaceship {
  private:
    const Object* location;
    int energy;
    unsigned int time {0};
    unsigned int move_energy_cost;
    unsigned int move_time_cost;
    std::vector<std::string> logs;

  public:
    Spaceship(const Object* const& loc, const unsigned int& energy) : location(loc), energy(energy) {}

    void move(DIRECTION dir);
    void orbit();
    void teleport();
    void ride();

    const DIRECTION doSeeHome() const;

    const Object* getCell() const { return this->location; }
    const int& getEnergy() const { return this->energy; }
    const unsigned int& getTime() const { return this->time; }
    const std::string getEnergyStr() const { return std::to_string(this->energy); }
    const std::string getTimeStr() const { return std::to_string(this->time); }
    void printLog() const;
};

#endif // SPACESHIP_HPP_INCLUDED
