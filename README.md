# README

## Advanced Topics in Object-Oriented Programming - Final Course Assignment (Winter 2024)

---

### Project Title:
**Episode 0: Star Wars**

---

### Description:
This project involves the creation of a time-dependent simulation game based on the **Model-View-Controller (MVC)** paradigm using **C++** with a focus on **design patterns**.

The game is set in the **Star Wars universe** and simulates the galactic empire's operations involving the transportation of crystals between space stations and fortresses, while defending against attacks from rebel ships. The empire's space is defined as a two-dimensional **Euclidean space** with a unit of 1000 kilometers. The simulation operates under the assumption of infinite space (no boundary conditions).

---

### Simulation Components:

#### Imperial Agents:
There are three types of agents in the simulation, representing soldiers of the Galactic Empire:
- **Midshipman**: Low-rank soldier.
- **Commander**: Mid-rank officer.
- **Admiral**: High-rank officer.

Each agent controls different types of spaceships:
- **Shuttle**: Used for transporting crystals between stations and fortresses.
- **TIE Bomber**: A combat ship patrolling space.
- **Star Destroyer**: A large combat ship with long-range capabilities.

#### Rebel Agents:
- **Millennium Falcon**: A smuggler ship that raids imperial transports and attacks empire ships.

---

### Space:
The simulation's space is a 2D Euclidean plane where:
- The positive **x-axis** represents east (90 degrees).
- The positive **y-axis** represents north (0 degrees).
- Movement direction is defined by an angle.
- Each space unit is 1000 kilometers.

---

### Game Mechanics:

1. **Shuttle**: 
   - Moves crystals between space stations and fortresses.
   - Has no weapons and can be attacked by rebels.
   
2. **TIE Bomber**: 
   - Patrols between different locations and engages in combat.
   - Can receive commands to move to specific coordinates.

3. **Star Destroyer**: 
   - Engages in long-range combat and patrols imperial space.
   - Capable of firing missiles.

4. **Millennium Falcon**: 
   - Smuggler ship controlled by rebels.
   - Can raid imperial ships and evade capture.

---

### Design Patterns:
The project must implement the **Singleton** pattern for the simulation model and use **Abstract Factory** for creating the different types of agents and ships. The goal is to structure the code in a modular and maintainable way, with an emphasis on using **smart pointers** for memory management and ensuring efficient performance.

---

### Commands:
The user interacts with the simulation via console commands to control the various ships and agents. Examples of supported commands include:
- **create**: Create a new ship or agent.
- **course**: Set the heading direction for a ship.
- **destination**: Set a target location for a ship.
- **go**: Advance the simulation by one hour.
- **status**: Display the current status of all entities in the simulation.

---

### Implementation Notes:
- The project must be implemented in **C++** using the **C++11** standard.
- Memory safety and performance are key; ensure proper usage of smart pointers and exception handling.
- The program should compile without errors or warnings using **g++** with the `-std=c++11` flag.
- Handle all input validation gracefully and provide meaningful error messages for invalid commands.

---
## How to Clone and Run the Code

To get started with this project, follow these steps:

### 1. Clone the Repository
Open your terminal and run the following commands:

```bash
git clone https://github.com/danielsal97/StarWars-simulation.git
cd StarWars-simulation 
g++ -std=c++11 -o game *.cpp
./game
```
