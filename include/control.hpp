#ifndef CONTROL_HPP_INCLUDED
#define CONTROL_HPP_INCLUDED

#include "space.hpp"
#include "spaceship.hpp"

class Control {
    private:
        Spaceship* ship;
        unsigned int row, col, energy, x_ship, y_ship;
        Space space;

        void scenario_one();
        void scenario_two();
        void scenario_three();

        void checkHome();
        void seenHome();

    public:
        void run();
};

#endif // CONTROL_HPP_INCLUDED
