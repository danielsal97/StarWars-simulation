//
// Created by daniel salame on 15/04/2024.
//
#include "SpaceStation.h"
#include <limits>
#ifndef FINELCPP_PROJECT_FORTRESS_H
#define FINELCPP_PROJECT_FORTRESS_H
class Fortress {
private:
    std::string name;
    double x, y;  // Coordinates
    unsigned int amount;

public:
    // Constructor declaration
    Fortress(std::string name, double x, double y, unsigned int capacity);

    // Function declarations
    void status() const;
    std::pair<double,double> getCords() const;
    void addSupply(int num);
    std::string getName() const;
};
#endif //FINELCPP_PROJECT_FORTRESS_H
