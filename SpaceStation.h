//
// Created by daniel salame on 14/04/2024.
//

#ifndef SPACE_STATION_H
#define SPACE_STATION_H

#include <string>
#include <iostream>
#include <utility>
using namespace std;

class SpaceStation {
private:
    std::string stationName;
    double x, y;
    int crystalCapacity;
    int crystalProductionRate;
    int storedCrystals; // Actual stored crystals

public:
    SpaceStation(std::string name, double x, double y, int capacity, int productionRate);

    void simulateTimePassing(int hours);
    void addCrystals(int amount);
    int getStoredCrystals() const;
    int takeCrystals(int amount);
    void updateCapacity();
    void status() const;
    std::pair<double, double> getCords() const;
    std::string getName() const;
};

#endif // SPACE_STATION_H

