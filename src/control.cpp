#include "control.hpp"

#include <iostream>

void Control::run()
{
    std::cin >> this->row >> this->col;
    std::cin >> this->x_ship >> this->y_ship >> this->energy;
    std::vector<std::vector<char>> raw_map(this->row, std::vector<char>(this->col, '0'));
    for (auto& i : raw_map) {
        for (auto& j : i) {
        std::cin >> j;
        }
    }
    this->space.buildMap(raw_map);
}

void Control::scenario_one()
{
    // TODO
}

void Control::scenario_two()
{
    // TODO
}

void Control::scenario_three()
{
    // TODO
}

void Control::checkHome()
{
    // TODO
}

void Control::seenHome()
{
    // TODO
}
