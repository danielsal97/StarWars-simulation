//
// Created by daniel salame on 20/04/2024.
//

#ifndef FINELCPP_PROJECT_DESTROYER_H
#define FINELCPP_PROJECT_DESTROYER_H
#include "spaceShip.h"
#include <iostream>
#include <utility>


class Destroyer : public SpaceShip {
private:
    const int destroyerSpeed = 2000;
    const int rocketSpeed = 3000;
    std::string spaceship_Name;
    std::string pilot_Name, destName;
    double x, y, update_x = 0, update_y = 0, rocket_x = 0, rocket_y = 0, updateRocket_x = 0, updateRocket_y = 0, dest_x =0, dest_y =0;
    double degree = 0;
    State state;

public:
    Destroyer(std::string  spaceshipName, std::string  pilotName, double x, double y);

    void stop() override;
    void destination(const std::string& dest, double x, double y) override;
    void status() override;
    std::pair<double, double> getCords() const;
    void course(double heading) override;
    void position(double x_cord, double y_cord) override;
    void updateCords();
    void shoot(double x_cord, double y_cord);
    void updateRocketCords();
    std::pair<double, double> getRocketCords() const;
    std::string getName() const;
};

#endif //FINELCPP_PROJECT_DESTROYER_H
