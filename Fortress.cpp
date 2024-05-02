//
// Created by daniel salame on 30/04/2024.
//
#include "Fortress.h"
#include <iostream>

Fortress::Fortress(std::string name, double x, double y, unsigned int capacity)
        : name(std::move(name)), x(x), y(y), amount(capacity) {}

void Fortress::status() const {
    std::cout << "Fortress " << name << " at position "
              << "(" << x << "," << y << "), Inventory: " << amount << std::endl;
}

std::pair<double, double> Fortress::getCords() const {
    return {x, y};
}

void Fortress::addSupply(int num) {
    amount += num;
}

std::string Fortress::getName() const {
    return name;
}