
#include "shuttle.h"

void Shuttle::stop()  {
    update_x =0;
    update_y =0;
    state =Stopped;
}

void Shuttle::destination(const string &dest, double x_cord, double y_cord) {
    state = MovingTo;
    dest_x = x_cord;
    dest_y = y_cord;
    double dis = sqrt(pow(x - x_cord, 2) + pow(y - y_cord, 2));
    update_x = (x_cord - x) / dis * speed / 1000;
    update_y = (y_cord - y) / dis * speed / 1000;
    destName = dest;
}

void Shuttle::status() {
    std::cout << "shuttle " <<spaceship_Name <<" at (" << x << ", " << y << "),"<<StateNames[state]<<" "<<destName<<", speed "<<speed<<"km/h, capacity: "<<supply<<" Strength: "<<power<<endl;
}

std::pair<double, double> Shuttle::getCords() const{
    return {x, y};
}

void Shuttle::powerup() {
    if (power <=20){
        power++;
    }
}

double Shuttle::getspeed() const {
    return speed;
}

pair<double, double> Shuttle::startSupply(double x_cord, double y_cord, string destTarget, string endTarget) {
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

void Shuttle::addsuupply(int num) {
    supply += num;
}

int Shuttle::removeSupply() {
    int get = supply;
    supply =0;
    return get;
}

string Shuttle::updateCords() {
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

int Shuttle::getCapacity() const {
    return capacity;
}
int Shuttle::getStrength() const{
    return power;
}
int Shuttle::attackedSucced(){
    state = Stopped;
    update_y = 0;
    update_x = 0;
    int num = capacity;
    capacity =0;
    return num;
}
void Shuttle::powerdown(){
    power--;
    if(power == 0) {
        state = Dead;
        update_x = 0;
        update_y = 0;
    }
}
string Shuttle::getName(){
    return spaceship_Name;
}