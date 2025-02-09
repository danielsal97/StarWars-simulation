# README

## Advanced Topics in Object-Oriented Programming - Final Course Assignment (Winter 2024)

### Project Title: Episode 0: Star Wars

## Description
This project involves the creation of a time-dependent simulation game based on the Model-View-Controller (MVC) paradigm using C++ with a focus on design patterns.

The game is set in the Star Wars universe and simulates the Galactic Empire's operations involving the transportation of crystals between space stations and fortresses while defending against attacks from rebel ships. The empire's space is defined as a two-dimensional Euclidean space with a unit of 1000 kilometers. The simulation operates under the assumption of infinite space (no boundary conditions).

## Simulation Components

### **Imperial Agents**
There are three types of agents in the simulation, representing soldiers of the Galactic Empire:
- **Midshipman**: Low-rank soldier.
- **Commander**: Mid-rank officer.
- **Admiral**: High-rank officer.

Each agent controls different types of spaceships:
- **Shuttle**: Used for transporting crystals between stations and fortresses.
- **TIE Bomber**: A combat ship patrolling space.
- **Star Destroyer**: A large combat ship with long-range capabilities.

### **Rebel Agents**
- **Millennium Falcon**: A smuggler ship that raids imperial transports and attacks empire ships.

### **Space Representation**
The simulation's space is a 2D Euclidean plane where:
- The positive x-axis represents east (90 degrees).
- The positive y-axis represents north (0 degrees).
- Movement direction is defined by an angle.
- Each space unit is 1000 kilometers.

## **Game Mechanics**

### **Shuttle**
- Moves crystals between space stations and fortresses.
- Has no weapons and can be attacked by rebels.

### **TIE Bomber**
- Patrols between different locations and engages in combat.
- Can receive commands to move to specific coordinates.

### **Star Destroyer**
- Engages in long-range combat and patrols imperial space.
- Capable of firing missiles.

### **Millennium Falcon**
- Smuggler ship controlled by rebels.
- Can raid imperial ships and evade capture.

## **Design Patterns**
- The project implements the **Singleton pattern** for the simulation model.
- Uses **Abstract Factory** for creating the different types of agents and ships.
- Emphasis on modular and maintainable code.
- Uses smart pointers for memory management.

## **Commands & Gameplay Instructions**
The user interacts with the simulation via console commands to control the various ships and agents. The following commands are supported:

### **Ship and Agent Creation**
- `create shuttle <name> <pilot> <x> <y>` – Create a new Shuttle.
- `create bomber <name> <pilot> <x> <y>` – Create a new TIE Bomber.
- `create destroyer <name> <pilot> <x> <y>` – Create a new Star Destroyer.
- `create falcon <name> <x> <y>` – Create a Millennium Falcon.
- `create midshipman <name>` – Create a Midshipman.
- `create commander <name>` – Create a Commander.
- `create admiral <name>` – Create an Admiral.

### **Ship Movement**
- `course <ship_name> <angle> <speed>` – Set the ship’s heading direction.
- `destination <ship_name> <x> <y>` – Set a target location for the ship.
- `go` – Advance the simulation by one hour.
- `stop <ship_name>` – Stop the movement of a ship.

### **Ship Status & Attacks**
- `status` – Display the current status of all entities in the simulation.
- `attack <attacker_name> <target_name>` – Attack a specific enemy ship.
- `shoot <destroyer_name> <x> <y>` – Fire a missile at a target location.

### **Shuttle Transport**
- `start_supply <shuttle_name> <station_name> <fortress_name>` – Start the transport of crystals between a space station and a fortress.

### **Display Controls**
- `default` – Reset the map to default parameters.
- `size <s>` – Set the map size (`6 ≤ s ≤ 30`).
- `zoom <ratio>` – Set the map scale (default: `2.0`).
- `pan <x> <y>` – Move the map center.
- `show` – Display the updated map.

### **Simulation Exit**
- `exit` – End the simulation and close the program.

## **Implementation Notes**
- The project is implemented in **C++11**.
- Ensure proper **memory safety and performance** using **smart pointers** and **exception handling**.
- The program should compile without errors or warnings using **g++ -std=c++11**.
- Handle all input validation gracefully and provide meaningful error messages for invalid commands.

## **How to Clone and Run the Code**

### **1. Clone the Repository**
```bash
$ git clone https://github.com/danielsal97/StarWars-simulation.git
$ cd StarWars-simulation
```

### **2. Compile and Run**
```bash
$ g++ -std=c++11 -o game *.cpp
$ ./game
```

Enjoy commanding the Galactic Empire and battling the Rebel forces in this strategic Star Wars simulation! 🚀

