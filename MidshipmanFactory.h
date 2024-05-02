//
// Created by daniel salame on 12/04/2024.
//

#ifndef FINELCPP_PROJECT_MIDSHIPMANFACTORY_H
#define FINELCPP_PROJECT_MIDSHIPMANFACTORY_H

#include "AgentFactory.h"
#include "Midshipman.h"

class MidshipmanFactory : public AgentFactory {
public:
    ImperialAgent* createAgent(const std::string& Military_Rank, const std::string& name) override {
        return new Midshipman(Military_Rank, name);  // Corrected to pass parameters.
    }
};

#endif // FINELCPP_PROJECT_MIDSHIPMANFACTORY_H
