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
//singelton
Model& Model::getInstance() {
    if (instance == nullptr) {
        instance = std::unique_ptr<Model>(new Model());
    }
    return *instance;
}
//print all statuses of objects in Model
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
//Responsible for managing time transitions and the behavior of objects between times
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
// add supply from fortress to shuttle
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
//remove supply from shuttle to target space-station
void Model::removeSupply(const string& shuttle, const string& dest){
   fortress[dest]->addSupply(shuttles[shuttle]->removeSupply());
}
//responsible for creating all types of agents;
void Model::createAgent(const string& rank, const string& pilotName) {
    // Ensure spaceshipName is unique here
    if (agents.find(pilotName) != agents.end()) {
        std::cerr << "Error: An agent with the name '" << pilotName << "' already exists." << std::endl;
        return;
    }
        if (rank == "commander"){
            CommanderFactory  factory;
            std::unique_ptr<ImperialAgent> agent(factory.createAgent(rank,pilotName));
            agents[pilotName] = std::move(agent);
        }
        else if (rank == "midshipman"){
            MidshipmanFactory factory;
            std::unique_ptr<ImperialAgent> agent(factory.createAgent(rank,pilotName));
            agents[pilotName] = std::move(agent);
        }
        else if ( rank == "admiral"){
            AdmiralFactory factory;
            std::unique_ptr<ImperialAgent> agent(factory.createAgent(rank,pilotName));
            agents[pilotName] = std::move(agent);
        }
        else{
            cerr<<"No suitable agent rank "<<endl;
            return;
        }
}
//responsible for creating all types of spaceships;
void Model::createSpaceship( string& spaceship_type, const string& spaceshipName, const string& coordinates = "",  const string& pilotName = "") {
    if (shuttles.find(spaceshipName) != shuttles.end() or bombers.find(spaceshipName) != bombers.end() or destroyers.find(spaceshipName) != destroyers.end()  or falcons.find(spaceshipName) != falcons.end())  {
        cerr << "Error: Spaceship '" << spaceshipName << "' already exists." << endl;
        return;  // Stop the creation process
    }
    pair<double, double> result = parseCoordinates(coordinates);
    if ( spaceship_type == "falcon") {
        std::unique_ptr<Falcon> myFalcon(new Falcon(spaceshipName, result.first, result.second));
        falcons[spaceshipName] = std::move(myFalcon);
        return;
    }
    if (agents.find(pilotName) == agents.end()){
        cerr<<pilotName<<"No existed pilot "<<endl;
        return;
    }
     spaceship_type = agents[pilotName]->suitableSpaceship();
    if ( spaceship_type == "shuttle"){
        unique_ptr<Shuttle> myShuttle(new Shuttle(spaceshipName, pilotName, result.first, result.second));
        shuttles[spaceshipName] = std::move(myShuttle);
        return;
    } else  if ( spaceship_type == "bomber"){
        std::unique_ptr<Destroyer> myDestroyer(new Destroyer(spaceshipName, pilotName, result.first, result.second));
        destroyers[spaceshipName] = std::move(myDestroyer);
        return;
    }
    else  if ( spaceship_type == "destroyer"){
        std::unique_ptr<Destroyer> myDestroyer(new Destroyer(spaceshipName, pilotName, result.first, result.second));
        destroyers[spaceshipName] = std::move(myDestroyer);
        return;
    }else{
        return;
    }
    }
//get time after "go" command
std::string Model::getTime() const {
    std::ostringstream oss;
    oss << "Time " << time<<":  ";
    return oss.str();
}
//parse coordinates into 2 doubles
std::pair<double, double> Model::parseCoordinates(const std::string& basicString) {
    double x_cord, y_cord;
    sscanf(basicString.c_str(), "(%lf, %lf)", &x_cord, &y_cord);
    return std::make_pair(x_cord, y_cord);
}
//loads file
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


    }
}
//create fortress
void Model::createFortress(const std::string& name, double x_cord, double y_cord, unsigned int amount){
    unique_ptr<Fortress> fort(new  Fortress(name, x_cord, y_cord, amount));
    fortress[name] = std::move(fort);
}

//create space-stations
void Model::createStation(const string& name, double x_cord, double y_cord, int cap, int prod){
    unique_ptr<SpaceStation> station(new SpaceStation(name, x_cord, y_cord, cap, prod));
    stations[name] = std::move(station);
}
//managing start_supply command
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

//managing destination command
void Model::destination(const string& spaceshipName, const string& destName) {
            std::pair<double, double> startStation_coordinates = stations[destName]->getCords();
            x=startStation_coordinates.first;
            y = startStation_coordinates.second;
            bombers[spaceshipName]->destination(destName,x,y);
}
//managing Course command
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
//managing priority queue for bomber patrol
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
//managing shoot command
void Model::shoot(const string& destroyerName, double x_cord, double y_cord){
    destroyers[destroyerName]->shoot(x_cord, y_cord);
}
//managing Attack command
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
