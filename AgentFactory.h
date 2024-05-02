//
// Created by daniel salame on 14/04/2024.
//

#ifndef FINELCPP_PROJECT_AGENTFACTORY_H
#define FINELCPP_PROJECT_AGENTFACTORY_H

#include "ImperialAgent-interface.h"

class AgentFactory {
public:
    virtual ImperialAgent* createAgent(const std::string& Military_Rank, const std::string& name) = 0;
    virtual ~AgentFactory() {}
};

#endif // FINELCPP_PROJECT_AGENTFACTORY_H
