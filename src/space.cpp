#include "space.hpp"

#include <iostream>

void Space::setMap(const unsigned int& row, const unsigned int& col) {
   this->map.assign(row, std::vector<Object*>(col));
   unsigned int ship_x, ship_y, ship_energy;
   std::cin >> ship_x >> ship_y >> ship_energy;
   this->ship = new Spaceship(ship_x, ship_y, ship_energy);
   for (size_t i = 0; i < row; ++i) {
      for (size_t j = 0; j < col; ++j) {
         unsigned int input_map;
         std::cin >> input_map;
         switch (input_map) {
            case 0:
               this->map.at(i).at(j) = nullptr;
               break;
            // TODO
         }
      }
   }
}
