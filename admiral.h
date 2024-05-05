//
// Created by daniel salame on 17/04/2024.
//

#ifndef FINELCPP_PROJECT_ADMIRAL_H
#define FINELCPP_PROJECT_ADMIRAL_H
#include "ImperialAgent-interface.h"
#include <string>
#include <utility>
using namespace std;
class Admiral : public ImperialAgent {
    string Military_Rank;
    string name;
    int assigned;
public:
    Admiral(std::string  Military_Rank, std::string  name): Military_Rank(std::move(Military_Rank)), name(std::move(name)),assigned(0){
    }
    //ensures taht each pilot will be connected to suitable spaceship by rank
    string suitableSpaceship() override {
        if (assigned == 0) {
            assigned =1;
            return "destroyer";
        }
        else{
            return name + " already associated with an spaceship ";
        }
    }
};
#endif //FINELCPP_PROJECT_ADMIRAL_H
