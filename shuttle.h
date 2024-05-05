#ifndef FINELCPP_PROJECT_SHUTTLE_H
#define FINELCPP_PROJECT_SHUTTLE_H

#include <iostream>
#include <utility>
#include "spaceShip.h"
#include <cmath>
#define shuttleSpeed 500
using namespace std;
class Shuttle : public SpaceShip {
    std::string spaceship_Name, destName, endName;
    std::string pilot_Name;
    double x = 0, y = 0, speed = shuttleSpeed, update_x = 0, update_y = 0, dest_x = 0, dest_y = 0;
    int power = 10, updateCordsFlag = 0, supply = 0, capacity = 5;
    State state;
    void course(double heading) override {
    }
    void position(double x_cords, double y_cords) override {
    }
public:
    Shuttle(std::string spaceshipName, std::string pilotName, double x, double y)
            : spaceship_Name(std::move(spaceshipName)), pilot_Name(std::move(pilotName)),
              x(x), y(y), speed(shuttleSpeed), update_x(0), update_y(0), dest_x(0), dest_y(0),
              power(10), updateCordsFlag(0), supply(0), capacity(5), state(Docked) {}

    void stop() override;
    void destination(const std::string& dest,double x_cord, double y_cord) override ;
    void status() override ;
    std::pair<double, double> getCords() const ;
    void powerup();
    double getspeed() const ;

pair<double,double> startSupply(double x_cord, double y_cord, string destTarget, string endTarget) ;
    void addsuupply(int num);
    int removeSupply();
    string updateCords();
    int getCapacity() const ;
    int getStrength() const ;
    int attackedSucced();
    void powerdown();
    string getName();


};

#endif //FINELCPP_PROJECT_SHUTTLE_H
