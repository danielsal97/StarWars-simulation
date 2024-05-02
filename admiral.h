//
// Created by daniel salame on 17/04/2024.
//

#ifndef FINELCPP_PROJECT_ADMIRAL_H
#define FINELCPP_PROJECT_ADMIRAL_H
#include "ImperialAgent-interface.h"
#include <string>
using namespace std;
class Admiral : public ImperialAgent {
    string Military_Rank;
    string name;
public:
    Admiral(const std::string& Military_Rank, const std::string& name): Military_Rank(Military_Rank), name(name){
       cout << Military_Rank << std::endl << name << std::endl;
    }

    void suitableSpaceship() override {
       cout << Military_Rank << "\tyessssss\t"<< name << std::endl;
    }
};
#endif //FINELCPP_PROJECT_ADMIRAL_H
