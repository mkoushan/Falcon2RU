#ifndef OBJECT_HPP_INCLUDE
#define OBJECT_HPP_INCLUDE

#include <utility>
#include <vector>
#include <string>

enum DIRECTION {
  UP = 0,
  RIGHT = 1,
  DOWN = 2,
  LEFT = 3,
  UP_RIGHT = 4,
  UP_LEFT = 5,
  DOWN_RIGHT = 6,
  DOWN_LEFT = 7,
  UNKNOWN = -69
};

typedef std::pair<unsigned int, unsigned int> Point;

class Object {
  private:
    bool is_home;
    std::vector<Object*> neighbors;
    const Object* target = nullptr;
    unsigned int special_energy_cost;
    unsigned int special_time_cost;
    Point location;

  public:
    Object (const Point& p, const bool is_home = false) : location(p), is_home(is_home) {}

    const Object* targetCell() const { return this->target; }
    void setTarget(Object* target) { this->target = target; }
    void setEnergyCost(const unsigned int& cost) { this->special_energy_cost = cost; }
    void setTimeCost(const unsigned int& cost) { this->special_time_cost = cost; }

    const unsigned int& getEnergyCost() const { return this->special_energy_cost; }
    const unsigned int& getTimeCost() const { return this->special_time_cost; }

    void setNeighbors(const std::vector<Object*>& neighbors) { this->neighbors = neighbors; }
    const std::vector<Object*>& getNeighbors() const { return this->neighbors; }

    const Point& getLocation() const { return this->location; }
    const std::string getLocationStr() const { return "(" + std::to_string(this->location.first) + "," + std::to_string(this->location.second) + ")"; }
};

#endif
