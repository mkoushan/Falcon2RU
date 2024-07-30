#include "control.hpp"
#include "space.hpp"

#include <iostream>
#include <ostream>
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
    this->start_cell = this->space.getCell({this->x_ship, this->y_ship});

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
    std::clog << "\nScenario #1:\n";
    this->newShip();
    // TODO

}

void Control::scenario_two()
{
    std::clog << "\nScenario #2:\n";
    this->newShip();

    try {
        // TODO
    } catch (std::domain_error const& ex) {
        this->ship->printLog();
        std::cerr << std::endl;
        std::cerr << "energy limit reached and we couldn't find the home :(\n";
    }
}

void Control::scenario_three()
{
    std::clog << "\nScenario #3:\n";
    this->newShip();

    try {

    } catch (std::domain_error const& ex) {
        this->ship->printLog();
        std::cerr << std::endl;
        std::cerr << "energy limit reached and we couldn't find the home :(\n";
    }
}

void Control::checkHome()
{
    if (this->ship->doSeeHome() != UNKNOWN) {
        this->seenHome();
    }
}

void Control::seenHome()
{
    const auto& home_dir = this->ship->doSeeHome();

    switch(home_dir) {
        case UP:
        case RIGHT:
        case DOWN:
        case LEFT:
            this->ship->move(home_dir);
        break;

        case UP_RIGHT:
            this->ship->move(UP);
            this->ship->move(RIGHT);
        break;

        case UP_LEFT:
            this->ship->move(UP);
            this->ship->move(LEFT);
        break;

        case DOWN_RIGHT:
            this->ship->move(DOWN);
            this->ship->move(RIGHT);
        break;

        case DOWN_LEFT:
            this->ship->move(DOWN);
            this->ship->move(LEFT);
        break;

        case UNKNOWN:
        // this should never happen
        break;
    }
    this->ship->printLog();
}

void Control::newShip()
{
    if (this->ship != nullptr) {
        delete this->ship;
    }
    this->ship = new Spaceship(start_cell);
}
