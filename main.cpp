#include <iostream>
#include "Controller.h"

using namespace std;
int main(int argc, char *argv[]) {
    cout.precision(2);
    cout << fixed;
    Controller controller;
    controller.run(argc,argv);



}
