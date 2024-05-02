//
// Created by daniel salame on 17/04/2024.
//

#ifndef FINELCPP_PROJECT_COMMANDERFACTORY_H
#define FINELCPP_PROJECT_COMMANDERFACTORY_H

#include "AgentFactory.h"
#include "Commander.h"

class CommanderFactory : public AgentFactory {
public:
    ImperialAgent* createAgent(const std::string& Military_Rank, const std::string& name) override {
        return new Commander(Military_Rank, name);  // Corrected to pass parameters.
    }
};
#endif //FINELCPP_PROJECT_COMMANDERFACTORY_H
