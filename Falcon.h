//
// Created by daniel salame on 20/04/2024.
//

#ifndef FINELCPP_PROJECT_FALCON_H
#define FINELCPP_PROJECT_FALCON_H
#include "spaceShip.h"
#include <iostream>
#include <utility>
#define FalconSpeed 2000
using namespace std;
class Falcon : public SpaceShip {
    std::string spaceship_Name;
    std::string pilot_Name;
    double x = 0, y= 0, speed = 0,update_x = 0, update_y = 0, degree = 0;
    int power = 5;
    State state = Docked;


    void destination(const std::string& dest,double x_cords, double y_cords) override {};
    void course(double heading) override{};
    void position(double x_cords, double y_cords) override{};

public:
    Falcon(std::string spaceshipName, string pilotName, double x_cords, double y_cords)
            : spaceship_Name(std::move(spaceshipName)), pilot_Name(std::move(pilotName)),
              x(x_cords), y(y_cords), speed(FalconSpeed), update_x(0), update_y(0),
              degree(0), power(5), state(Docked) {}
    void status() override;
    std::pair<double, double> getCords() const;
    void course(double heading, int falconSpeed);
    void position( double x_cord, double y_cord,int falconSpeed);
    void updateCords();
    void kill();
    int getStrength() const;
    void powerup();
    void powerdown();
    void stop() override;
    string getName();
};
#endif //FINELCPP_PROJECT_FALCON_H
