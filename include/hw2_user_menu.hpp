#ifndef HW2_USER_MENU_HPP
#define HW2_USER_MENU_HPP

#include <iostream>
#include <string>
#include <vector>
#include "hw2_food_types.hpp"
#include "hw2_menu_item.hpp"

namespace menu {

class Menu {

    public:
    // Constructor
    Menu(double totalCost = 0.0, TasteProfile avgTaste = {0.0, 0.0, 0.0, 0.0, 0.0}, std::vector<std::unique_ptr<MenuItem>>&& menuItems = {});

    // Compute Average Taste Profile
    TasteProfile averageTasteProfileOfMenu() const;

    // Adding Item
    void addItem(std::unique_ptr<MenuItem> mi);

    // Remove Item
    bool removeItem(std::size_t index);

    // Updating Taste Profile of the Menu Items
    bool updateTasteProfileOfMenuItem(std::size_t index, double increment);

    // Find Total Cost
    double getTotalCost();

    // Print Menu
    void printMenu() const;


    private:
    double totalCost;
    TasteProfile avgTaste;
    std::vector<std::unique_ptr<MenuItem>> menuItems;
};

class User {

    public:
    // Constructor
    User(const std::string& userName = "None", const std::string& userSurname = "None", const std::string& userGender = "None");
    User(const std::string& userName, const std::string& userSurname, const std::string& userGender, Menu&& userMenu);

    // Printing User Info
    void getUserInfo() const;

    // Getter of User's menu
    const Menu& getUserMenu() const;

    private:
    std::string userName;
    std::string userSurname;
    std::string userGender;
    Menu userMenu;

};

struct Catalog {
    std::vector<Starter> starters;
    std::vector<Salad> salads;
    std::vector<MainCourse> mainCourses;
    std::vector<Drink> drinks;
    std::vector<Appetizer> appetizers;
    std::vector<Dessert> desserts;
};

bool loadCatalogFromJSON(const std::string& menu, Catalog& catalog);

} // namespace menu

#endif // HW2_USER_MENU_HPP