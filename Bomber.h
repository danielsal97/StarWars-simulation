//
// Created by daniel salame on 19/04/2024.
//

#ifndef FINELCPP_PROJECT_BOMBER_H
#define FINELCPP_PROJECT_BOMBER_H

#include <iostream>
#include <string>
#include <cmath>
#include "spaceShip.h"

class Bomber : public SpaceShip {
private:
    std::string spaceship_Name;
    std::string pilot_Name, destName;
    double x = 0, y = 0, speed, update_x, update_y, dest_x, dest_y;
    State state;

public:
    Bomber(std::string  spaceshipName, std::string  pilotName, double x, double y);

    void stop() override;
    void destination(const std::string& dest, double x_cord, double y_cord) override;
    void updateCords();
    void course(double heading) override;
    void position(double x_cord, double y_cord) override;
    void position(double x_cord, double y_cord, std::string nameTar);
    void status() override;
    std::pair<double, double> getCords() const;
    std::string getName() const;
    int flag = 1;

};
#endif // FINELCPP_PROJECT_BOMBER_H

