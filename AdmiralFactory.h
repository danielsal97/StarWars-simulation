//
// Created by daniel salame on 17/04/2024.
//

#ifndef FINELCPP_PROJECT_ADMIRALFACTORY_H
#define FINELCPP_PROJECT_ADMIRALFACTORY_H

#include "ImperialAgent-interface.h"
#include "AgentFactory.h"
#include "admiral.h"

class AdmiralFactory : public AgentFactory {
public:
    ImperialAgent* createAgent(const string& Military_Rank, const string& name) override {
        return new Admiral(Military_Rank, name);  // Corrected to pass parameters.
    }
};
#endif //FINELCPP_PROJECT_ADMIRALFACTORY_H
