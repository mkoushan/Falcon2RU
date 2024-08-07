#ifndef CONTROL_HPP_INCLUDED
#define CONTROL_HPP_INCLUDED

#include "space.hpp"
#include "spaceship.hpp"

class Control {
    private:
        Spaceship* ship = nullptr;
        const Object* start_cell;
        unsigned int row, col, energy, x_ship, y_ship;
        Space space;

        void newShip();

        void scenario_one();
        void suspirium();
        void suspirium2();
        void suspirium3();
        void suspirium4();

        void randomMove();
        void scenario_two();
        void scenario_three();

        void checkHome();
        void seenHome();

    public:
        void run();
};

#endif // CONTROL_HPP_INCLUDED
