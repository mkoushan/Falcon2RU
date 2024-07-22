#include "spaceship.hpp"

#include <stdexcept>
#include <iostream>

Spaceship::Spaceship(const unsigned int& x, const unsigned int& y, const unsigned int& energy) {
   try {
      this->setLocation(x, y);
      this->setEnergy(energy);

   } catch (std::invalid_argument& err) {
      std::cerr << err.what() << std::endl;
   }
}

void Spaceship::setLocation(const unsigned int& x, const unsigned int& y) {
   this->location = {x, y};
}

void Spaceship::setEnergy(const unsigned int& energy) {
   this->energy = energy;
}

// TODO
/*
void Spaceship::move (char direction, vector <vector<Object*>> &map) {
    switch (direction) {
        case 'n' : {
            if (location -> get_y() == 0) {
                throw out_of_range ("You can't go higher than that!");
            }
            char u = map.at(location -> get_x() ).at(location -> get_y() - 1) -> show();
            if (u == '2' or u == '3' or u == '4'){
                throw out_of_range ("There is an obstacle in the way, we can't move there !");
            }
            else if (energy < move_energy_cost){
                throw out_of_range ("Energy is low, we cannot move !");
            }
            else {
                energy -= move_energy_cost;
                location -> set_y(location -> get_y()-1);
            }
        }
    }
}
*/
