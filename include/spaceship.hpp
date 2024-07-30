#ifndef SPACESHIP_HPP_INCLUDED
#define SPACESHIP_HPP_INCLUDED

#include "object.hpp"
#include "space.hpp"

class Spaceship {
  private:
    const Object* location;
    unsigned int energy;
    unsigned int time {0};
    unsigned int move_energy_cost;
    unsigned int move_time_cost;
    std::vector<std::string> logs;

  public:
    void move(DIRECTION dir);
    void orbit();
    void teleport();
    void ride();

    const std::string getEnergyStr() const { return std::to_string(this->energy); }
    const std::string getTimeStr() const { return std::to_string(this->time); }
    void printLog() const;
};

#endif // SPACESHIP_HPP_INCLUDED
