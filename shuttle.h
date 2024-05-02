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

    void stop() override {
        std::cout << "Shuttle has stopped." << std::endl;
    }
    void destination(const std::string& dest,double x_cords, double y_cords) override {
        std::cout << "Heading to " << dest << "." << std::endl;
    }

    void status() override {
        std::cout << "shuttle " <<spaceship_Name <<" at (" << x << ", " << y << "),"<<StateNames[state]<<" "<<destName<<", speed "<<speed<<"km/h, capacity: "<<supply<<" Strength: "<<power<<endl;
    }
    std::pair<double, double> getCords() const {
        return {x, y};
    }
    void powerup(){
        if (power <=20){
            power++;
        }
    }
    double getspeed() const {
        return speed;
    }

pair<double,double> startSupply(double x_cord, double y_cord, string destTarget, string endTarget) {
        updateCordsFlag = 1;
        double dis = sqrt(std::pow(x-x_cord, 2) + pow(y-y_cord, 2));
        double new_x, new_y;
        dest_x= x_cord;
        dest_y= y_cord;
        new_x = x_cord -x;
        new_y = y_cord-y;
        if(new_x ==0 and new_y == 0){
           state = Docked;
            updateCordsFlag= 0;
            return {0,0};
        }
        update_x+= new_x/dis*speed/1000;
        update_y+= new_y/dis*speed/1000;
        state = MovingTo;
        destName = std::move(destTarget);
        endName = std::move(endTarget);
    return {1,0};

    }
    void addsuupply(int num){
        supply += num;
    }
    int removeSupply(){
        int get = supply;
        supply =0;
        return get;
    }
    string updateCords() {
        if (updateCordsFlag ==0){
            return "";
        }
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
            return endName;
        }
        return "";
    }
    int getCapacity() const{
        return capacity;
    }
    int getStrength() const{
        return power;
    }
    int attackedSucced(){
        state = Stopped;
        update_y = 0;
        update_x = 0;
        int num = capacity;
        capacity =0;
        return num;
    }
    void powerdown(){
        power--;
        if(power == 0) {
            state = Dead;
            update_x = 0;
            update_y = 0;
        }
    }
    string getName(){
        return spaceship_Name;
    }


};

#endif //FINELCPP_PROJECT_SHUTTLE_H
