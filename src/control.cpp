#include "control.hpp"

#include <iostream>

void Control::run()
{
  unsigned int row, col;
  std::cin >> row >> col;
  std::vector<std::vector<char>> raw_map(row, std::vector<char>(col, '0'));
  for (auto& i : raw_map) {
    for (auto& j : i) {
      std::cin >> j;
    }
  }

  this->space.buildMap(raw_map);
}
