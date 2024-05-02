//
// Created by daniel salame on 04/04/2024.
//

#include "Controller.h"
#include <iostream>
#include "Fortress.h"
#include <algorithm>
using namespace std;


void Controller::run(int i, char **pString) {
    processCommand(i,pString);
}

void Controller::modelCommands(Model &model, const string& command) {
    stringstream iss(command);
    string first_word, second_word, third_word, forth_word, fifth_word, sixth;

    iss >> first_word >> second_word;

  if (second_word == "start_supply") {
        iss>>third_word>>forth_word;
        model.startSupply(first_word,third_word,forth_word);
    }
  else if(second_word =="destination"){
        iss>>third_word;
        model.destination(first_word,third_word);
    }
  else if (second_word == "course") {
        iss >> third_word >> forth_word;
        if (!iss.fail()) {
            // The fifth word was successfully extracted
            model.Course(first_word, third_word, std::stoul(forth_word));
        } else {
            // The fifth word extraction failed
            model.Course(first_word, third_word, 0); // Or any default value you prefer
        }
    }
  else if (second_word == "shoot") {
        iss >> third_word; // Extract the first double with the comma
        third_word.erase(0, 1);
        // Remove the comma
        third_word.erase(std::remove(third_word.begin(), third_word.end(), ','), third_word.end());

        iss >> forth_word; // Extract the second double with the comma
        // Remove the comma
        forth_word.erase(std::remove(forth_word.begin(), forth_word.end(), ','), forth_word.end());
        forth_word.pop_back();
        model.shoot(first_word, stoi(third_word), stoi(forth_word));
    }    else if (second_word == "attack") {
        iss >> third_word; // Extract the first double with the comma
        model.Attack(first_word,third_word);
    }
  else {
            cout << "Unsupported command or missing parameters." << endl;
        }
    }


void Controller::processCommand(int i, char **argv) {
    MatrixView& view = MatrixView::getInstance();
    Model &model = Model::getInstance();
    model.createFortress("DS",40,10,100000);
//    if (i > 1) {
//        model.loadStationsFromFile(argv[1]); // Assuming argv[1] is the path to site.dat
//    }
    model.loadStationsFromFile("/Users/danielsa/CLionProjects/finelCPP-project/sites.dat"); // Assuming argv[1] is the path to site.dat


    vector<string> commandQueue;
    string command;

    while(true) {
        cout << model.getTime() << " Enter command: ";
        getline(cin, command);
        stringstream iss(command);
        string first_word, second_word, third_word, forth_word, fifth_word, sixth;
        iss>>first_word>>second_word>> third_word >> forth_word >> fifth_word >> sixth;
        if (first_word == "create" ) {

            if (second_word == "shuttle") {
//                iss >> third_word >> forth_word >> fifth_word >> sixth;
                if (!iss.fail()) {
                    model.create(third_word, forth_word, fifth_word + sixth);
                } else {
                    cout << "Error: Missing parameters for 'create shuttle' command." << endl;
                }
            }
            else if(second_word == "bomber"){

//                iss >> third_word >> forth_word >> fifth_word >> sixth;
                if (!iss.fail()) {
                    model.createBomber(third_word, forth_word, fifth_word + sixth);
                } else {
                    cout << "Error: Missing parameters for 'create bomber' command." << endl;
                }
            }else if(second_word == "destroyer"){

//                iss >> third_word >> forth_word >> fifth_word >> sixth;
                if (!iss.fail()) {
                    model.createDestroyer(third_word, forth_word, fifth_word + sixth);
                } else {
                    cout << "Error: Missing parameters for 'create destroyer' command." << endl;
                }
            }else if(second_word == "falcon"){

//                iss >> third_word >> forth_word >> fifth_word ;
                if (!iss.fail()) {
                    model.createFalcon(third_word, forth_word, forth_word + fifth_word);
                } else {
                    cout << "Error: Missing parameters for 'create falcon' command." << endl;
                }
            }
            else if (second_word == "midshipman") {
//                iss >> third_word;
                model.createMid(second_word, third_word);
            }
            else if (second_word == "commander") {
//                iss >> third_word;
                model.createCommander(second_word, third_word);
            } else if (second_word == "admiral") {
//                iss >> third_word;
                model.createAdmiral(second_word, third_word);
            }
        }
        else if(first_word == "pan"){
//            iss>> third_word;
            view.changeOrigin(stoi(second_word), stoi(third_word));
        } else if(first_word == "zoom"){
            view.changeScale(stoi(second_word));
        }
        else if ( first_word == "size"){
            view.changeSize(stoi(second_word));
        }
        else if(first_word == "default"){
            view.defaultView();
        }
        else if (command =="show"){
          view.printMatrix();
        }
        else if (command == "go") {
            while (!commandQueue.empty()) {
                string queuedCommand = commandQueue.front();
                modelCommands(model, queuedCommand);
                commandQueue.erase(commandQueue.begin()); // Remove the processed command
            }
            model.go();
        }else if (command == "status"){
            model.status();
        }
        else if (command != "exit") {
            commandQueue.push_back(command);
        } else {
            exit(0);
        }
    }
}