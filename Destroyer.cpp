//
// Created by daniel salame on 30/04/2024.
//
#include "Destroyer.h"
#include <iostream>
#include <cmath>
#include <utility>

Destroyer::Destroyer(std::string  spaceshipName, std::string  pilotName, double x, double y)
        : spaceship_Name(std::move(spaceshipName)), pilot_Name(std::move(pilotName)), x(x), y(y), dest_x(0), dest_y(0), state(MovingOnCourse) {}

void Destroyer::stop() {
    std::cout << "Shuttle has stopped." << std::endl;
}

void Destroyer::destination(const std::string& dest, double x_cord, double y_cord) {
    state = MovingTo;
    dest_x = x_cord;
    dest_y = y_cord;
    double dis = sqrt(pow(x - x_cord, 2) + pow(y - y_cord, 2));
    update_x = (x_cord - x) / dis * destroyerSpeed / 1000;
    update_y = (y_cord - y) / dis * destroyerSpeed / 1000;
    destName = dest;
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
    if (update_x > dest_x - x or x == dest_x) {
        x = dest_x;
    } else {
        x += update_x;
    }
    if (update_y > dest_y - y or  y == dest_y) {
        y = dest_y;
    } else {
        y += update_y;
    }
    if(x == dest_x and y == dest_y){
        update_x =0;
        update_y =0;
        state =Docked;
    }
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