#ifndef OBJECT_HPP_INCLUDE
#define OBJECT_HPP_INCLUDE

#include <utility>
#include <string>
#include <map>

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
    char type;
    std::map<DIRECTION, Object*> neighbors;
    const Object* target = nullptr;
    unsigned int special_energy_cost;
    unsigned int special_time_cost;
    Point location;

  public:
    Object (const Point& p, const char type = '0') : location(p), type(type) {}
    const char& show() const { return this->type; }
    const bool isHome() const { return this->show() == '5'; }

    const Object* targetCell() const { return this->target; }
    void setTarget(Object* target) { this->target = target; }
    void setEnergyCost(const unsigned int& cost) { this->special_energy_cost = cost; }
    void setTimeCost(const unsigned int& cost) { this->special_time_cost = cost; }

    const unsigned int& getEnergyCost() const { return this->special_energy_cost; }
    const unsigned int& getTimeCost() const { return this->special_time_cost; }
    const Object* const & getObject(const DIRECTION& dir) const { return this->neighbors.at(dir); }

    void setNeighbors(const std::map<DIRECTION, Object*>& neighbors) { this->neighbors = neighbors; }
    const std::map<DIRECTION, Object*>& getNeighbors() const { return this->neighbors; }

    const Point& getLocation() const { return this->location; }
    const std::string getLocationStr() const { return "(" + std::to_string(this->location.first) + "," + std::to_string(this->location.second) + ")"; }
};

#endif
