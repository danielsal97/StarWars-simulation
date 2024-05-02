//
// Created by daniel salame on 30/04/2024.
//
#include "Bomber.h"
#include <iostream>
#include <cmath>
#include <utility>

Bomber::Bomber(std::string  spaceshipName, std::string  pilotName, double x, double y)
        : spaceship_Name(std::move(spaceshipName)), pilot_Name(std::move(pilotName)), x(x), y(y),speed(1000), update_x(0),  update_y(0),  dest_x(0), dest_y(0), state(Docked){}

void Bomber::stop() {
update_y = 0;
update_x = 0;
state= Stopped;
}

void Bomber::destination(const std::string& dest, double x_cord, double y_cord) {
    state = MovingTo;
    flag = 0;
    dest_x = x_cord;
    dest_y = y_cord;
    double dis = sqrt(pow(x - x_cord, 2) + pow(y - y_cord, 2));
    update_x = (x_cord - x) / dis * speed / 1000;
    update_y = (y_cord - y) / dis * speed / 1000;
    destName = dest;
}

void Bomber::updateCords() {
    if(x == dest_x and y == dest_y){
            flag =1;
        }
        if (abs(update_x) > abs(dest_x - x) or x == dest_x) {
            x = dest_x;
        } else {
            x += update_x;
        }
        if (abs(update_y) > abs(dest_y - y) or y == dest_y) {
            y = dest_y;
        } else {
            y += update_y;
        }
}

void Bomber::course(double heading) {
    state = MovingOnCourse;
    update_y = cos(heading * (M_PI / 180)) * speed / 1000;
    update_x = sin(heading * (M_PI / 180)) * speed / 1000;
}

void Bomber::position(double x_cord, double y_cord) {
            state = MovingTo;
        double dis = sqrt(pow(x-x_cord,2)+pow(y-y_cord,2));
        double new_x, new_y;
        new_x = x_cord -x;
        new_y = y_cord-y;
        update_x = new_x/dis*speed/1000;
        update_y= new_y/dis*speed/1000;
}

void Bomber::position(double x_cord, double y_cord, std::string nameTar) {
    destName = std::move(nameTar);
    dest_x = x_cord;
    dest_y = y_cord;
    position(x_cord, y_cord);
}

void Bomber::status() {
    std::cout << "Bomber " << spaceship_Name << " at (" << x << "," << y << "), " << "State: " << StateNames[state] << ", " << destName << ", " << speed << "km/h" << std::endl;
}

std::pair<double, double> Bomber::getCords() const {
    return {x, y};
}

std::string Bomber::getName() const {
    return spaceship_Name;
}