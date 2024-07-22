#include "control.hpp"

#include <iostream>

void Control::run() {
   unsigned int row, col;
   std::cin >> row >> col;
   space.setMap(row, col);
}
