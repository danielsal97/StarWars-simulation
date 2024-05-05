//
// Created by daniel salame on 10/04/2024.
//

#ifndef FINELCPP_PROJECT_MIDSHIPMAN_H
#define FINELCPP_PROJECT_MIDSHIPMAN_H

#include "ImperialAgent-interface.h"

class Midshipman : public ImperialAgent {
    string Military_Rank;
    int assigned;
    string name;
public:
Midshipman(const std::string& Military_Rank, const std::string& name): Military_Rank(std::move(Military_Rank)), assigned(0), name(std::move(name)){
}
string suitableSpaceship() override {
    if (assigned == 0) {
        assigned =1;
        return "shuttle";
    }
    else{
        return name + " Already associated with an spaceship ";
    }
}

};

#endif // FINELCPP_PROJECT_MIDSHIPMAN_H
