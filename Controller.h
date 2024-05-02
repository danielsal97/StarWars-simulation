//
// Created by daniel salame on 04/04/2024.
//

#ifndef FINELCPP_PROJECT_CONTROLLER_H
#define FINELCPP_PROJECT_CONTROLLER_H
#include <string>
#include <sstream>
using namespace std;
#include "Model.h"
#include "Midshipman.h"
#include "shuttle.h"
#include "spaceShip.h"
#include "MatrixView.h"
class Controller {

public:
    static void run(int i, char **argv);
private:
    static void modelCommands( Model &model, const string& command);
    static void processCommand(int i, char **pString);
};


#endif //FINELCPP_PROJECT_CONTROLLER_H
