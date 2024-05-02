//////
////// Created by daniel salame on 30/04/2024.
//////
#include "Falcon.h"
#include <iostream>
#include <cmath>
#include <utility>



void Falcon::status(){
    if (state == Dead){
        cout<< "falcon " <<spaceship_Name<<" is "<<StateNames[state]<<"!!!" <<endl;
    }
    if (state == MovingOnCourse){
        std::cout<<"falcon " <<spaceship_Name <<" at (" << x << ", " << y << "), "<<StateNames[state]<<" "<<degree<<" degree, speed "<<speed<<"km/h "<<"Strength: "<<power<<endl;
    }
    else
        std::cout<<"falcon " <<spaceship_Name <<" at (" << x << ", " << y << "),"<< "speed "<<speed<<"km/h "<<"Strength: "<<power<<endl;
}
void Falcon::course(double heading, int falconSpeed) {
    state = MovingOnCourse;
    degree = heading;
    speed = falconSpeed;
    update_y = cos(heading * (M_PI / 180))*falconSpeed/1000;
    update_x = sin(heading * (M_PI / 180))*falconSpeed/1000;

}
pair<double,double> Falcon::getCords() const  {
    return {x, y};
}
void Falcon::position(double x_cord, double y_cord, int falconSpeed)  {
    speed = falconSpeed;
    state = MovingTo;
    double dis = sqrt(pow(x-x_cord,2)+pow(y-y_cord,2));
    double new_x, new_y;
    new_x = x_cord -x;
    new_y = y_cord-y;
    update_x = new_x/dis*speed/1000;
    update_y= new_y/dis*speed/1000;
}
void Falcon::updateCords() {
    x+=update_x;
    y+=update_y;
}
void Falcon::kill() {
    state = Dead;
    update_x = 0;
    update_y =0;
}
int Falcon::getStrength() const {
    return power;
}
void Falcon::powerup() {
    power++;
}
void Falcon::powerdown() {
    power--;
    if(power == 0){
        kill();
    }
}
void Falcon::stop()  {
    state = Stopped;
    update_x = 0;
    update_y = 0;
}
string Falcon::getName() {
    return spaceship_Name;
}