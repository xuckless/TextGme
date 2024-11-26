# TextGame

A text-based adventure game implemented in C++. Players navigate through a series of levels, interact with decision trees, and engage in turn-based combat with enemies.

## Features

- **Level Progression**: Traverse through multiple levels implemented using a linked list (`LevelHandler`).
- **Decision Tree**: Dynamic decision-making using a custom `ScenarioHandler` and `Scenes` classes.
- **Combat System**: Turn-based combat with options to attack, heal, defend, and use special abilities.
- **Dynamic Player System**: Create unique characters with customizable stats and abilities.
- **Artifact Collection**: Acquire and manage artifacts to boost stats or unlock new abilities.

## Technologies Used

- **C++**: Core game implementation.
- **CMake**: Build system.
- **Object-Oriented Design**: Modular structure for levels, players, and enemies.

## Installation

### Prerequisites

- A C++ compiler (e.g., GCC, Clang, or MSVC)
- CMake (version 3.15 or later)
- Optional: CLion IDE for development

### Steps

1. Clone the repository:
   ```
   git clone https://github.com/username/TextGame.git
   cd TextGame
   ```

2.	Create a build directory and configure the project with CMake:
    ```
  	mkdir build
    cd build
    cmake ..
    ```

3.	Build the project
```
     cmake --build
```
4.  Run the game
```
    ./TextGame
```


---------------------------------------


Gameplay

	1.	Character Selection:
	•	At the start of the game, select a character with unique abilities:
	•	Ban: Steals health from enemies.
	•	Gojo: Replenishes aura during combat.
	•	Madara: Deals extra damage.
	2.	Exploration:
	•	Use the decision tree to explore the environment and make choices.
	3.	Combat:
	•	Battle enemies in turn-based combat with options to:
	•	Attack: Deal damage to the enemy.
	•	Heal: Recover health using aura.
	•	Defend: Reduce damage from the enemy’s next attack.
	•	Special Move: High-damage attack (costs extra aura).
	4.	Artifacts:
	•	Collect artifacts to enhance stats or gain abilities.

Directory Structure

```
.
├── AsciiArt.h
├── BaseLevel.cpp
├── BaseLevel.h
├── CMakeLists.txt
├── DynamicArray.h
├── Enemy.cpp
├── Enemy.h
├── Level.h
├── LevelHandler.cpp
├── LevelHandler.h
├── LevelOne.cpp
├── LevelOne.h
├── LevelThree.cpp
├── LevelThree.h
├── LevelTwo.cpp
├── LevelTwo.h
├── Levels.cpp
├── Levels.h
├── Player.cpp
├── Player.h
├── ScenarioHandler.h
├── Scenes.h
├── Utilities.cpp
├── Utilities.h
└── main.cpp

```



















