# itu-hw2-menu-project
Overview
This project implements a modular C++ application that simulates a restaurant menu system.
It allows users to generate, view, and modify menus based on individual taste preferences or randomized selections.
The project demonstrates object-oriented programming principles such as inheritance, polymorphism, encapsulation, and smart pointer usage (std::unique_ptr).
Features
Load menu data from a JSON file
Interactive console interface for user input
Menu generation methods:
Random menu creation
Taste-profile-based menu creation
Add, remove, and update menu items dynamically
Compute average taste balance and total cost of the user’s menu
Support for multiple food categories (Starter, Salad, Main Course, Drink, Dessert, Appetizer)
Project Structure
hw2/
│
├── include/
│   ├── hw2_food_types.hpp        # Derived food type classes (Starter, Salad, etc.)
│   ├── hw2_menu_item.hpp         # Base class MenuItem and TasteProfile structure
│   ├── hw2_user_menu.hpp         # User and Menu class declarations
│   ├── hw2_recommender.hpp       # Menu recommendation and random generation functions
│   └── hw2_json_loader.hpp       # JSON file loading utilities
│
├── src/
│   ├── hw2_menu.cpp              # Implementation of Menu, User, and TasteProfile
│   ├── hw2_recommender.cpp       # Logic for menu recommendation and randomization
│   └── hw2_main.cpp              # Main entry point (user interface)
│
├── data/
│   └── menu.json                 # Example data file for menu items
│
└── CMakeLists.txt                # Build configuration
Build Instructions
Requirements
C++17 or newer
CMake (version 3.10 or above)
nlohmann/json header library
Compilation
mkdir build
cd build
cmake ..
cmake --build .
Run Instructions
After successful build, run the executable from the build directory:
./hw2
The program will prompt the user for:
Name and gender information
Menu generation choice (random or taste-based)
Option to edit or save the generated menu
Example Interaction
=== Restaurant Bot ===
I'll create menus for you based on your preferences.

First name: John
Last name: Doe
Gender (Mr / Mrs): Mr

--- MAIN MENU ---
1. Show my menu
2. Add / remove / update item
3. Create RANDOM menu
4. Create menu for TASTE PROFILE
0. Exit
Key Concepts Demonstrated
Inheritance and Polymorphism:
Each food category class (e.g., Starter, Salad, Drink) inherits from MenuItem and overrides printMenuItem().
Encapsulation:
Data such as taste attributes, prices, and customization options are protected and accessible only through getter/setter methods.
Smart Pointers (std::unique_ptr):
Used for memory safety and ownership of dynamically allocated menu items.
JSON Integration:
Menu data is loaded dynamically at runtime using nlohmann/json.
Author
Mehmet Görkem Keskin
Istanbul Technical University – Control and Automation Engineering
