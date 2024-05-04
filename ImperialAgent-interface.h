//
// Created by daniel salame on 10/04/2024.
//

#ifndef FINELCPP_PROJECT_IMPERIALAGENT_INTERFACE_H
#define FINELCPP_PROJECT_IMPERIALAGENT_INTERFACE_H

#include <string>
#include <iostream>

class ImperialAgent {
public:
    virtual string suitableSpaceship() = 0;
    virtual ~ImperialAgent() = default;  // Provide a definition, even if empty.
};

#endif //FINELCPP_PROJECT_IMPERIALAGENT_INTERFACE_H
