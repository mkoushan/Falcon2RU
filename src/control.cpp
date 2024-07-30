#include "control.hpp"

#include <iostream>
#include <stdexcept>

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

    try {
        this->scenario_one();
        this->scenario_two();
        this->scenario_three();
    } catch (std::invalid_argument const& ex) {
        this->ship->printLog();
        std::cerr << std::endl;
        std::cerr << ex.what();
    } catch (...) {
        this->ship->printLog();
        std::cerr << std::endl;
        std::cerr << "even I don't know what happened. good luck\n";
    }
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
    if (this->ship->doSeeHome() != UNKNOWN) {
        this->seenHome();
    }
}

void Control::seenHome()
{
    // TODO
}
