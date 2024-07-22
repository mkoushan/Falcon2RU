#ifndef SPACESHIP_HPP_INCLUDED
#define SPACESHIP_HPP_INCLUDED

#include "object.hpp"

class Spaceship {
   private:
      Point location;
      unsigned int energy;
      // TODO
      // const int move_energy_cost = 1;
   public:
      Spaceship(const unsigned int& x, const unsigned int& y, const unsigned int& energy);
      // TODO
      // void move (char, std::vector <std::vector<Object*>>&);
      void setLocation(const unsigned int& x, const unsigned int& y);
      void setEnergy(const unsigned int& energy);
      const unsigned int& getEnergy() const {return this->energy;}
};

#endif // SPACESHIP_HPP_INCLUDED
