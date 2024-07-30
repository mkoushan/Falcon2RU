#ifndef REACHED_HPP_INCLUDED
#define REACHED_HPP_INCLUDED

#include <exception>

class Reached : public std::exception {
    public:
    char* what() {
        return "SPACESHIP REACHED HOME!!!";
    }
};

#endif // REACHED_HPP_INCLUDED
