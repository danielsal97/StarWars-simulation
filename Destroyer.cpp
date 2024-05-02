//
// Created by daniel salame on 30/04/2024.
//
#include "Destroyer.h"
#include <iostream>
#include <cmath>
#include <utility>

Destroyer::Destroyer(std::string  spaceshipName, std::string  pilotName, double x, double y)
        : spaceship_Name(std::move(spaceshipName)), pilot_Name(std::move(pilotName)), x(x), y(y), state(MovingOnCourse) {}

void Destroyer::stop() {
    std::cout << "Shuttle has stopped." << std::endl;
}

void Destroyer::destination(const std::string& dest, double x_cord, double y_cord) {
    std::cout << "Heading to " << dest << "." << std::endl;
}

void Destroyer::status() {
    std::cout << "Destroyer " << spaceship_Name << " at (" << x << ", " << y << "), " << StateNames[state];
    if (state == MovingOnCourse)
        std::cout << " " << degree << " deg, ";
    std::cout << "speed " << destroyerSpeed << "km/h" << std::endl;
}

std::pair<double, double> Destroyer::getCords() const {
    return {x, y};
}

void Destroyer::course(double heading) {
    degree = heading;
    state = MovingOnCourse;
    update_y = std::cos(heading * (M_PI / 180)) * destroyerSpeed / 1000;
    update_x = std::sin(heading * (M_PI / 180)) * destroyerSpeed / 1000;
}

void Destroyer::position(double x_cord, double y_cord) {
    state = MovingTo;
    double dis = sqrt(pow(x-x_cord,2)+pow(y-y_cord,2));
    double new_x, new_y;
    new_x = x_cord -x;
    new_y = y_cord-y;
    update_x = new_x/dis*destroyerSpeed/1000;
    update_y= new_y/dis*destroyerSpeed/1000;
}

void Destroyer::updateCords() {
    x += update_x;
    y += update_y;
}

void Destroyer::shoot(double x_cord, double y_cord) {
    double dis = sqrt(pow(x-x_cord,2)+pow(y-y_cord,2));
    double new_x, new_y;
    new_x = x_cord - x;
    new_y = y_cord - y;
    updateRocket_x = new_x/dis*rocketSpeed/1000;
    updateRocket_y= new_y/dis*rocketSpeed/1000;
}

void Destroyer::updateRocketCords() {
    rocket_x += x + updateRocket_x;
    rocket_y += y + updateRocket_y;
}

std::pair<double, double> Destroyer::getRocketCords() const {
    return {rocket_x, rocket_y};
}

std::string Destroyer::getName() const {
    return spaceship_Name;
}