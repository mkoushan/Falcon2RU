#include "control.hpp"
#include "dice.hpp"
#include "object.hpp"
#include "space.hpp"
#include "reached.hpp"

#include <iostream>
#include <stdexcept>
#include <set>
#include <algorithm>

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
    }
}

void Control::suspirium()
{
    static std::set<Point> visited;
    if (visited.count(this->ship->getCell()->getLocation()) == 1) {
        return;
    } visited.insert(this->ship->getCell()->getLocation());
    this->checkHome();
    try {
        this->ship->move(RIGHT);
        this->suspirium();
        this->ship->move(LEFT);
    } catch (std::invalid_argument const& ex) {}

    try {
        this->ship->move(UP);
        this->suspirium();
        this->ship->move(DOWN);
    } catch (std::invalid_argument const& ex) {}

    try {
        this->ship->move(LEFT);
        this->suspirium();
        this->ship->move(RIGHT);
    } catch (std::invalid_argument const& ex) {}

    try {
        this->ship->move(DOWN);
        this->suspirium();
        this->ship->move(UP);
    } catch (std::invalid_argument const& ex) {}
}

void Control::scenario_one()
{
    std::clog << "\nScenario #1:\n";
    this->newShip();

    try {
        this->suspirium();
    } catch (Reached& ex) {
        std::clog << ex.what() << std::endl;
    }
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
    } catch (Reached& ex) {
        std::cout << ex.what() << std::endl;
    }
}

void Control::scenario_three()
{
    std::clog << "\nScenario #3:\n";
    this->newShip();

    try {
        while (this->ship->getEnergy() > 0) {
            this->checkHome();
            switch(this->ship->getCell()->show()) {
                case '0':
                    if (this->ship->getCell()->getEnergyCost() == 12) { // space object is close
                        switch (roll({{0, 67}, {1, 33}})) {
                            case 0:
                                this->ship->orbit();
                            break;

                            case 1:
                                this->randomMove();
                            break;
                        }
                    } else { // empty cell
                        this->randomMove();
                    }
                break;

                case '1':
                    // 0:ride, 1:move
                   if (roll({{0, 0.75}, {1, 25}}) == 0) {
                       this->ship->ride();
                   } else {
                       this->randomMove();
                   }
                break;

                case '4': {

                    switch (roll({{0, 0.33}, {1, 0.33}, {2, 0.34}})) {
                        case 0:
                            this->ship->teleport();
                        break;

                        case 1:
                            this->randomMove();
                        break;

                        case 2:
                            // 0:move, 1:teleport
                            if (roll({{0, 0.5}, {1, 0.5}}) == 0) {
                                this->randomMove();
                            } else {
                                this->ship->teleport();
                            }
                        break;
                    }
                }
                break;
            }
        }
    } catch (std::domain_error const& ex) {
        this->ship->printLog();
        std::cerr << std::endl;
        std::cerr << "energy limit reached and we couldn't find the home :(\n";
    } catch (Reached& ex) {
        std::cout << ex.what() << std::endl;
    }
}

void Control::randomMove()
{
    try {
        switch(roll({{0, 0.25}, {1, 0.25}, {2, 0.25}, {3, 0.25}})) {
             case 0: // move up
                 this->ship->move(UP);
             break;

             case 1: // move right
                 this->ship->move(RIGHT);
             break;

             case 2: // move down
                 this->ship->move(DOWN);
             break;

             case 3: // move left
                 this->ship->move(LEFT);
             break;
        }
    } catch (std::invalid_argument const& ex) {
        // everything is ok don't worry'
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
    throw Reached();
}

void Control::newShip()
{
    if (this->ship != nullptr) {
        delete this->ship;
    }
    this->ship = new Spaceship(this->start_cell, this->energy);
}
