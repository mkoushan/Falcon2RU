#ifndef SPACESHIP_HPP_INCLUDED
#define SPACESHIP_HPP_INCLUDED

#include "object.hpp"
#include "space.hpp"

class Spaceship {
  private:
    Object* location;
    unsigned int energy;

  public:
    void setLocation(const Object*& location);
    void setEnergy(const unsigned int& energy);
    const unsigned int& getEnergy() const {return this->energy;}
};

#endif // SPACESHIP_HPP_INCLUDED
