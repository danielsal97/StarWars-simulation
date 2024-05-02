//
// Created by daniel salame on 17/04/2024.
//

#ifndef FINELCPP_PROJECT_COMMANDER_H
#define FINELCPP_PROJECT_COMMANDER_H
#include "ImperialAgent-interface.h"
#include <string>
using namespace std;
class Commander : public ImperialAgent{
    string Military_Rank;
    string name;
public:
    Commander(const std::string& Military_Rank, const std::string& name): Military_Rank(Military_Rank), name(name){
        std::cout << Military_Rank << std::endl << name << std::endl;
    }

    void suitableSpaceship() override {
        std::cout << Military_Rank << "yessssss"<< name << std::endl;
    }
};
#endif //FINELCPP_PROJECT_COMMANDER_H
