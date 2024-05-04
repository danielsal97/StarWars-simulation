//
// Created by daniel salame on 10/04/2024.
//

#ifndef FINELCPP_PROJECT_MIDSHIPMAN_H
#define FINELCPP_PROJECT_MIDSHIPMAN_H

#include "ImperialAgent-interface.h"

class Midshipman : public ImperialAgent {
    string Military_Rank;
string name;
public:
Midshipman(const std::string& Military_Rank, const std::string& name): Military_Rank(Military_Rank), name(name){
    std::cout << Military_Rank << std::endl << name << std::endl;
}

string suitableSpaceship() override {
return "shuttle";
}
};

#endif // FINELCPP_PROJECT_MIDSHIPMAN_H
