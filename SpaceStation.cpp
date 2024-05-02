//
// Created by daniel salame on 30/04/2024.
//
#include "SpaceStation.h"
#include <iostream>
SpaceStation::SpaceStation(std::string name, double x, double y, int capacity, int productionRate)
        : stationName(std::move(name)), x(x), y(y), crystalCapacity(capacity), crystalProductionRate(productionRate), storedCrystals(0) {
}

void SpaceStation::simulateTimePassing(int hours) {
    storedCrystals += hours * crystalProductionRate;
    if (storedCrystals > crystalCapacity)
        storedCrystals = crystalCapacity; // Cap at max capacity
}

void SpaceStation::addCrystals(int amount) {
    storedCrystals += amount;
    if (storedCrystals > crystalCapacity)
        storedCrystals = crystalCapacity; // Prevent overfilling
}

int SpaceStation::getStoredCrystals() const {
    return storedCrystals;
}

int SpaceStation::takeCrystals(int amount) {
    if (amount > storedCrystals)
        amount = storedCrystals;
    storedCrystals -= amount;
    return amount;
}

void SpaceStation::updateCapacity() {
    crystalCapacity += crystalProductionRate;
}

void SpaceStation::status() const {
    std::cout << "Station " << stationName << " at position (" << x << "," << y << "), Inventory: " << storedCrystals << std::endl;
}

std::pair<double, double> SpaceStation::getCords() const {
    return {x, y};
}

std::string SpaceStation::getName() const {
    return stationName;
}