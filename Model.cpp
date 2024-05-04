//
// Created by daniel salame on 06/04/2024.
//

#include <iostream>
#include <sstream>
#include "Model.h"
#include <utility>
#include <fstream>
#include <vector>
#include <queue>
#include <functional>
#include "CommanderFactory.h"
#include "AdmiralFactory.h"
#include "Fortress.h"
#include <algorithm>
#define SPACE_SIZE 1000
using namespace std;
std::unique_ptr<Model> Model::instance = nullptr;

Model& Model::getInstance() {
    if (instance == nullptr) {
        instance = std::unique_ptr<Model>(new Model());
    }
    return *instance;
}

void Model::status() {
    for (const auto& fort : fortress) {
        fort.second->status();
    }
    for (const auto& station : stations) {
        station.second->status();
    }
    for (const auto& shuttle : shuttles) {
        shuttle.second->status();
    }
    for (const auto& bomber : bombers) {
        bomber.second->status();
    }
    for (const auto& destroyer : destroyers) {
        destroyer.second->status();
    }
    for (const auto& falcon : falcons) {
        falcon.second->status();
    }
}

void Model::go() {

    time++;
    for (const auto &station: stations)
        station.second->updateCapacity();
    for (const auto &shuttle: shuttles) {
        string end = shuttle.second->updateCords();
        if (!end.empty() and fortress[end]) {
            if (supplyFlag == 1) {
                supplyFlag = 0;
                addSupply(shuttle.first, supplyStationName);
            } else if (supplyFlag == 2) {
                removeSupply(shuttle.first, end);
            }
            startSupply(shuttle.first, end, end);
        }
    }
    for (auto  const& falcon: falcons){
        falcon.second->updateCords();
    }
    for (const auto &destroyer:destroyers ){
        destroyer.second->updateCords();
        destroyer.second->updateRocketCords();
        for (const auto &falcon:falcons ){

            if (destroyer.second->getRocketCords() == falcon.second->getCords()){
                falcon.second->kill();
            }
        }
    }
    for (const auto &bomber: bombers) {
        bomber.second->updateCords();
        if (bombers[bomber.first]->flag == 1) {
        if(bomberRoutes[bomber.first].empty()) {
            prioritizeStationsForBomber(bomber.second->getName());
        }

        if (!bomberRoutes[bomber.first].empty()) {

                bombers[bomber.first]->flag = 0;
                SpaceStation s = bomberRoutes[bomber.first].top();
                auto cords = s.getCords();

                bombers[bomber.first]->position(cords.first, cords.second, s.getName());
                bomberRoutes[bomber.first].pop();
            }

        }

    }
}
void Model::addSupply(const string& shuttle, const string& station){
    if(stations[station]->getStoredCrystals() > shuttles[shuttle]->getCapacity() ){
        shuttles[shuttle]->addsuupply((shuttles[shuttle]->getCapacity()));
        stations[station]->takeCrystals(shuttles[shuttle]->getCapacity());
    }
    else{
        shuttles[shuttle]->addsuupply((stations[station]->getStoredCrystals()));
        stations[station]->takeCrystals(stations[station]->getStoredCrystals());
    }
}
void Model::removeSupply(const string& shuttle, const string& dest){
   fortress[dest]->addSupply(shuttles[shuttle]->removeSupply());
}
void Model::createMid(const string& spaceshipName, const string& pilotName){

// Ensure spaceshipName is unique here
        if (agents.find(pilotName) != agents.end()) {
            std::cerr << "Error: An agent with the name '" << pilotName << "' already exists." << std::endl;
            return;
        } else {
            MidshipmanFactory factory;
            std::unique_ptr<ImperialAgent> agent(factory.createAgent(spaceshipName, pilotName));
            agents[pilotName] = std::move(agent);
        }

}
void Model::createCommander(const string& spaceshipName, const string& pilotName){
        CommanderFactory  factory;
        std::unique_ptr<ImperialAgent> agent(factory.createAgent(spaceshipName,pilotName));

// Ensure spaceshipName is unique here
        if (agents.find(pilotName) != agents.end()) {
            std::cerr << "Error: An agent with the name '" << pilotName << "' already exists." << std::endl;
        } else {
            agents[pilotName] = std::move(agent);


// Print all agents to verify contents of the map
        std::cout << "Current list of agents:" << std::endl;
        for (const auto& pair : agents) {
            pair.second->suitableSpaceship();
        }

    }

}
void Model::createAdmiral(const string& spaceshipName, const string& pilotName){
    AdmiralFactory  factory;
    std::unique_ptr<ImperialAgent> agent(factory.createAgent(spaceshipName,pilotName));
// Ensure spaceshipName is unique here
    if (agents.find(pilotName) != agents.end()) {
        std::cerr << "Error: An agent with the name '" << pilotName << "' already exists." << std::endl;
    } else {
        agents[pilotName] = std::move(agent);


// Print all agents to verify contents of the map
        std::cout << "Current list of agents:" << std::endl;
        for (const auto& pair : agents) {
            pair.second->suitableSpaceship();
        }

    }
}
void Model::create(const string& spaceshipName, const string& pilotName, const string& coordinates = "") {
    if (agents.find(pilotName) == agents.end()){
        cerr<<pilotName<<"No existed pilot "<<endl;
        return;
    }
    if (shuttles.find(spaceshipName) != shuttles.end()) {
        cerr << "Error: Spaceship '" << spaceshipName << "' already exists." << endl;
        return;  // Stop the creation process
    }
    pair<double, double> result = parseCoordinates(coordinates);
    unique_ptr<Shuttle> myShuttle(new Shuttle(spaceshipName, pilotName, result.first, result.second));

    shuttles[spaceshipName] = std::move(myShuttle);  // Store shuttle by name
    for (const auto& pair : agents) {
        pair.second->suitableSpaceship();
    }
}
void Model::createBomber(const string& spaceshipName, const string& pilotName, const string& coordinates = "") {
    if (shuttles.find(spaceshipName) != shuttles.end()) {
        cerr << "Error: Spaceship '" << spaceshipName << "' already exists." << endl;
        return;  // Stop the creation process
    }
    pair<double, double> result = parseCoordinates(coordinates);
    std::unique_ptr<Bomber> myBomber(new Bomber(spaceshipName, pilotName, result.first, result.second));

    bombers[spaceshipName] = std::move(myBomber);  // Store shuttle by name
    for (const auto& pair : agents) {
        pair.second->suitableSpaceship();
    }
}
void Model::createDestroyer(const string& spaceshipName, const string& pilotName, const string& coordinates = "") {
    if (destroyers.find(spaceshipName) != destroyers.end()) {
        cerr << "Error: Spaceship '" << spaceshipName << "' already exists." << endl;
        return;  // Stop the creation process
    }
    pair<double, double> result = parseCoordinates(coordinates);
    std::unique_ptr<Destroyer> mydest(new Destroyer(spaceshipName, pilotName, result.first, result.second));

    destroyers[spaceshipName] = std::move(mydest);  // Store shuttle by name
    for (const auto& pair : agents) {
        pair.second->suitableSpaceship();
    }
}
void Model::createFalcon(const string& spaceshipName, const string& pilotName, const string& coordinates = "") {
    if (falcons.find(spaceshipName) != falcons.end()) {
        cerr << "Error: Spaceship '" << spaceshipName << "' already exists." << endl;
        return;  // Stop the creation process
    }
    pair<double, double> result = parseCoordinates(coordinates);
    std::unique_ptr<Falcon> mydest(new Falcon(spaceshipName, pilotName, result.first, result.second));

    falcons[spaceshipName] = std::move(mydest);  // Store shuttle by name
    for (const auto& pair : agents) {
        pair.second->suitableSpaceship();
    }
}
std::string Model::getTime() const {
    std::ostringstream oss;
    oss << "Time " << time<<":  ";
    return oss.str();
}
std::pair<double, double> Model::parseCoordinates(const std::string& basicString) {
    double x_cord, y_cord;
    sscanf(basicString.c_str(), "(%lf, %lf)", &x_cord, &y_cord);
    return std::make_pair(x_cord, y_cord);
}

void Model::loadStationsFromFile(const string &filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Unable to open file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
        stringstream ss(line);
        string type, name, coords;
        string capacity, production;

        getline(ss, type, ',');
        getline(ss, name, ',');
        getline(ss, coords, ')');
        getline(ss, capacity, ',');
        getline(ss, production, ',');
        getline(ss, capacity, ',');

        coords.erase(std::remove(coords.begin(), coords.end(), ' '), coords.end());
        coords+=')';
        pair<double, double> result = parseCoordinates(coords);
        createStation(name, result.first,result.second,stoi(production),stoi(capacity));
//        if (type == "station") {
//            unique_ptr<SpaceStation> station(new SpaceStation(name, result.first, result.second, stoi(production), stoi(capacity)));
//            stations[name] = move(station);
//        }
    }
}
void Model::createFortress(const std::string& name, double x_cord, double y_cord, unsigned int amount){
    unique_ptr<Fortress> fort(new  Fortress(name, x_cord, y_cord, amount));
    fortress[name] = std::move(fort);

}


void Model::createStation(const string& name, double x_cord, double y_cord, int cap, int prod){
    unique_ptr<SpaceStation> station(new SpaceStation(name, x_cord, y_cord, cap, prod));
    stations[name] = std::move(station);
}
void Model::startSupply(const std::string& shuttleName, const std::string& startStation, const std::string& endStation) {
    if (shuttles.find(shuttleName) == shuttles.end()){
        cout<<"shuttle "<<shuttleName <<" doesnt exists"<<endl;
        return;
    }
    supplyStationName =startStation;
    if(startStation == endStation){

       pair<double, double> endStation_coordinates = fortress[endStation]->getCords();
       pair<double,double> check = shuttles[shuttleName]->startSupply(endStation_coordinates.first,endStation_coordinates.second,startStation, endStation);
        if(check.first == 0 and check.second == 0) {
            removeSupply(shuttleName, endStation);
            shuttles[shuttleName]->powerup();

        }
    }
    else {
        std::pair<double, double> startStation_coordinates = stations[startStation]->getCords();
        std::pair<double, double> cords = shuttles[shuttleName]->startSupply(startStation_coordinates.first,
                                                                             startStation_coordinates.second,
                                                                             startStation, endStation);
        if (cords.first == 0 and cords.second == 0) {

            std::pair<double, double> endStation_coordinates = fortress[endStation]->getCords();
            shuttles[shuttleName]->startSupply(endStation_coordinates.first, endStation_coordinates.second,
                                               startStation, endStation);

            if (cords.first == 0 and cords.second == 0) {
                supplyFlag = 2;
                shuttles[shuttleName]->powerup();
            }
        }
    }


    }


void Model::destination(const string& spaceshipName, const string& destName) {
            std::pair<double, double> startStation_coordinates = stations[destName]->getCords();
            x=startStation_coordinates.first;
            y = startStation_coordinates.second;
            bombers[spaceshipName]->destination(destName,x,y);
}

void Model::Course(const string& spaceshipName, const string& degree ,unsigned int speed =0) {
    if (bombers.find(spaceshipName) != bombers.end()) {
        bombers[spaceshipName]->course(stoi(degree));
    } else if (destroyers.find(spaceshipName) != destroyers.end()) {

        destroyers[spaceshipName]->course(stoi(degree));
    }else if (falcons.find(spaceshipName) != falcons.end()) {
        falcons[spaceshipName]->course(stoi(degree), static_cast<int>(speed));
    } else {
        // Handle the case where the spaceship does not exist
        cout << "Error: Spaceship '" << spaceshipName << "' not found." << endl;
    }
}

void Model::prioritizeStationsForBomber( const std::string& bomberName) {
    if (bombers.find(bomberName) == bombers.end() || !bombers[bomberName]) {
        std::cerr << "Bomber '" << bomberName << "' not found or pointer is null." << std::endl;
        return;
    }

    std::priority_queue<SpaceStation, std::vector<SpaceStation>, DistanceComparator> pq((DistanceComparator(&*(bombers)[bomberName])));
    for (const auto& stationPair : stations) {
        pq.push(*stationPair.second);
    }
    bomberRoutes[bomberName] =pq;

}

void Model::shoot(const string& destroyerName, double x_cord, double y_cord){
    destroyers[destroyerName]->shoot(x_cord, y_cord);

}
void Model::Attack(const string& falconName,const string& ShutleName){
    auto falconCords = falcons[falconName]->getCords();
    auto shuttleCords = shuttles[ShutleName]->getCords();
    double Shuttledis = sqrt(pow(falconCords.first - shuttleCords.first, 2) + pow(falconCords.second - shuttleCords.second, 2));
    double BomberDis =251;
    for(const auto& bomber:bombers ){
        auto BomberCords = bomber.second->getCords();
        if(sqrt(pow(BomberCords.first - shuttleCords.first, 2) + pow(BomberCords.second - shuttleCords.second, 2)) < static_cast<double>(251)/SPACE_SIZE) {
            BomberDis = sqrt(pow(BomberCords.first - shuttleCords.first, 2) + pow(BomberCords.second - shuttleCords.second, 2));
            continue;
        }
    }
    shuttles[ShutleName]->powerdown();
    if (Shuttledis < 100 and falcons[falconName]->getStrength() > shuttles[ShutleName]->getStrength() and BomberDis > static_cast<double>(250)/SPACE_SIZE){
        shuttles[ShutleName]->attackedSucced();
        falcons[falconName]->powerup();
    }
    else{
        falcons[falconName]->powerdown();
    }
    falcons[falconName]->stop();
}
