// Model.h

// Created by Daniel Salame on 06/04/2024.

#ifndef FINELCPP_PROJECT_MODEL_H
#define FINELCPP_PROJECT_MODEL_H

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include "spaceShip.h"
#include "shuttle.h"
#include "ImperialAgent-interface.h"
#include "SpaceStation.h"
#include "Fortress.h"
#include "MidshipmanFactory.h"
#include "Bomber.h"
#include "Destroyer.h"
#include "Falcon.h"
#include "MatrixView.h"
using namespace std;
struct DistanceComparator {
    DistanceComparator() = default;

    const Bomber* bomber;
    explicit DistanceComparator(const Bomber* bomb) : bomber(bomb) {
        if (!bomber) {
            throw std::runtime_error("Bomber pointer is not set in comparator.");
        }
    }
    bool operator()(const SpaceStation& a, const SpaceStation& b) const {
        auto a_cords = a.getCords();
        auto b_cords = b.getCords();
        auto bomber_cords = bomber->getCords();
        double distA = sqrt(pow(a_cords.first - bomber_cords.first, 2) + pow(a_cords.second - bomber_cords.second, 2));
        double distB = sqrt(pow(b_cords.first - bomber_cords.first, 2) + pow(b_cords.second - bomber_cords.second, 2));
        return distA > distB;
    }
};

class Model {
    std::unordered_map<std::string, std::unique_ptr<Shuttle>> shuttles;
    std::unordered_map<std::string, std::unique_ptr<Bomber>> bombers;
    std::unordered_map<std::string, std::unique_ptr<Destroyer>> destroyers;
    std::unordered_map<std::string, std::unique_ptr<Falcon>> falcons;
    std::unordered_map<std::string, std::unique_ptr<Fortress>> fortress;
    map<string,  std::priority_queue<SpaceStation, std::vector<SpaceStation>, DistanceComparator>> bomberRoutes;

public:
    static Model &getInstance();
    string getTime() const;
    static std::pair<double, double> parseCoordinates(const std::string& basicString);
    void status();
    void go();
    void createAgent(const string& spaceshipName, const string& pilotName);
    void createFortress(const std::string& name, double x, double y, unsigned int amount);
    void createSpaceship(string& spaceship_type, const string &spaceshipName ,  const string& coordinates , const string &pilotName);

    Model(const Model&) = delete;
    Model& operator=(const Model&) = delete;
    void loadStationsFromFile(const string& filename);
    void createStation(const string& name, double x, double y, int cap, int prod);
    void startSupply(const std::string& shuttleName, const std::string& startStation, const std::string& endStation);
    void destination(const string& spaceshipName, const string& destName);

    void Course(const string& spaceshipName, const string& degree,unsigned int speed);
    void addSupply(const string& shuttle, const string& station);
    void removeSupply(const string& shuttle, const string& fortress);
    void shoot(const string& destroyerName, double x_cord, double y_cord);
    void Attack(const string& falconName,const string& ShutleName);
    void  prioritizeStationsForBomber( const string& bomber);
    friend class MatrixView;
private:
    std::unordered_map<std::string, std::unique_ptr<SpaceStation>> stations;
    std::unordered_map<std::string, std::unique_ptr<ImperialAgent>> agents;

    static std::unique_ptr<Model> instance;
    double x =0,y = 0;
     int time = 0, supplyFlag =1;
     string supplyStationName;
    Model(){}

};

#endif //FINELCPP_PROJECT_MODEL_H
