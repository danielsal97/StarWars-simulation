//
// Created by daniel salame on 04/04/2024.
//

#include "Controller.h"
#include <iostream>
#include "Fortress.h"
#include <algorithm>
using namespace std;
unsigned int Controller::safeStoui(const std::string& str) {
    try {
        // Convert to unsigned long first
        unsigned long value = std::stoul(str);

        // Check if within the range of an unsigned int
        if (value > std::numeric_limits<unsigned int>::max()) {
            std::cerr << "Error: The value '" << str << "' exceeds the maximum value for an unsigned int." << std::endl;
            exit(1); // or handle as needed
        }

        return static_cast<unsigned int>(value); // Safe cast since value is in range
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: Could not convert '" << str << "' to integer. " << e.what() << std::endl;
        exit(1); // Return a default value or handle as needed
    } catch (const std::out_of_range& e) {
        std::cerr << "Out of range: The string '" << str << "' is out of unsigned int range. " << e.what() << std::endl;
        exit(1); // Return a default value or handle as needed
    }
}
int Controller::safeStoi(const std::string& str) {
    try {
        return std::stoi(str);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: Could not convert '" << str << "' to integer. " << e.what() << std::endl;
        exit(1); // Return a default value or handle as needed
    } catch (const std::out_of_range& e) {
        std::cerr << "Out of range: The string '" << str << "' is out of integer range. " << e.what() << std::endl;
        exit(1); // Return a default value or handle as needed
    }
}
void Controller::run(int i, char **pString) {
    processCommand(i,pString);
}
void Controller::processCommand(int i, char **argv) {
    MatrixView& view = MatrixView::getInstance();
    Model &model = Model::getInstance();
    model.createFortress("DS",40,10,100000);
    if (i > 1) {
        model.loadStationsFromFile(argv[1]); // Assuming argv[1] is the path to site.dat
    }


    vector<string> commandQueue;
    string command;

    while(true) {
        cout << model.getTime() << " Enter command: ";
        getline(cin, command);
        stringstream iss(command);
        string first_word, second_word, third_word, fourth_word, fifth_word, sixth;
        int successCount = 0;

        // Attempt to extract each word and increment success count for each successful extraction
        if (iss >> first_word) ++successCount;
        if (iss >> second_word) ++successCount;
        if (iss >> third_word) ++successCount;
        if (iss >> fourth_word) ++successCount;
        if (iss >> fifth_word) ++successCount;
        if (iss >> sixth) ++successCount;
        if (first_word == "create" ) {
            //creates pilot need 3 arguments
            if (successCount == 3) {
                model.createAgent(second_word, third_word);
                continue;
                //creates falcons by 5 arguments
            } else if (successCount == 5) {
                model.createSpaceship(second_word, third_word, fourth_word + fifth_word, sixth);
                continue;
                //creates spaceships by 6 arguments
            } else if (successCount == 6) {
                model.createSpaceship(second_word, third_word, fifth_word + sixth, fourth_word);
                continue;
            }
        }
        //changes pan (origin) of matrix
        else if(first_word == "pan"){
            view.changeOrigin(safeStoi(second_word), safeStoi(third_word));
          // changes the scale of matrix
        } else if(first_word == "zoom"){
            view.changeScale(safeStoui(second_word));
        }
        //changing the size of matrix
        else if ( first_word == "size"){
            int arg= safeStoi(second_word);
            if (arg <= 6 or arg >30 ){
                cerr<<"number should be grater then 6 and less then 31"<<endl;
            }
            view.changeSize(arg);
        }
        //changing all matrix params to default
        else if(first_word == "default"){
            view.defaultView();
        }
        //show matrix
        else if (command =="show"){
            view.printMatrix();
        }
        //changing time by +1
        else if (command == "go") {
            while (!commandQueue.empty()) {
                string queuedCommand = commandQueue.front();
                modelCommands(model, queuedCommand);
                commandQueue.erase(commandQueue.begin()); // Remove the processed command
            }
            model.go();
            //show all objects status
        }else if (command == "status"){
            model.status();
        }
        //add command to a queue so it will run after "go" command
        else if (command == "start_supply" or command == "destination" or command == "course" or command == "attack" or command =="shoot") {
            commandQueue.push_back(command);
            //exit program
        }  else if (command == "exit") {
            exit(0);
        }else{
            //commmand that are not valid
            cerr<<command<<": Not valid"<<endl;
            exit(1);
        }
    }
}
//after the commands stored in queue they will be init by those functions
void Controller::modelCommands(Model &model, const string& command) {
    stringstream iss(command);
    string first_word, second_word, third_word, forth_word, fifth_word, sixth;

    iss >> first_word >> second_word;
    //start suuply can work only for shuttle spaceship
  if (second_word == "start_supply") {
        iss>>third_word>>forth_word;
        model.startSupply(first_word,third_word,forth_word);
    }
  //changing destination of spaceship by destination name of space-station;
  else if(second_word =="destination"){
        iss>>third_word;
        model.destination(first_word,third_word);
    }
      //changing course of spaceship;
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
            cerr << "Unsupported command or missing parameters." << endl;
        }
    }




