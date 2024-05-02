//
// Created by daniel salame on 10/04/2024.
//

#ifndef FINELCPP_PROJECT_SPACESHIP_H
#define FINELCPP_PROJECT_SPACESHIP_H

#include <string>
#include <map>
class SpaceShip {
public:
    enum State {
        Stopped = 0,
        Docked = 1,
        Dead = 2,
        MovingTo = 3,
        MovingOnCourse =4
    };

    std::map<State, std::string> StateNames = {
            {Stopped, "Stopped"},
            {Docked, "Docked"},
            {Dead, "Dead"},
            {MovingTo, "Heading To"},
            {MovingOnCourse, "Heading on course"}
    };
    virtual void stop() = 0;
    virtual void destination(const std::string& dest, double x, double y) = 0;
    virtual void course(double heading) = 0;
    virtual void position(double x, double y) = 0;
    virtual void status() = 0;
    virtual ~SpaceShip() {}
};

#endif //FINELCPP_PROJECT_SPACESHIP_H

