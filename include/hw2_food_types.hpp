#ifndef HW2_FOOD_TYPES_HPP
#define HW2_FOOD_TYPES_HPP

#pragma once
#include "hw2_menu_item.hpp"   
#include <string>
#include <memory>

namespace menu {

class Starter: public MenuItem {
    public:
    // Constructor
    Starter(std::string n, double p, TasteProfile t, bool hot = false);
    
    // Unique getter func. of Starter 
    bool isHot() const;   
    
    // Override Virtual Func
    void printMenuItem() const override;

    // Setter
    void setHot(bool h);

    std::unique_ptr<MenuItem> clone() const override {
        return std::make_unique<Starter>(*this);
    }
    
    private:
    bool hot;
};

class Salad: public MenuItem {
    public:
    // Constructor
    Salad(std::string n, double p, TasteProfile t, bool topping = false, std::string toppingName = "None");

    // U.G.F of Salad
    bool hasTopping() const;
    std::string getToppingName() const;
    // Setter
    void setTopping(bool t);
    void setToppingName(const std::string& tn);
    // Override Virtual Func
    void printMenuItem() const override;
    
    // Set Salad Price
    void setSaladPrice();
    
    // Adding Topping due to User needs
    void addTopping(const std::string& tn);
    
    // Removing topping due to User needs 
    void removeTopping();

    std::unique_ptr<MenuItem> clone() const override {
        return std::make_unique<Salad>(*this);
    }
    
    private:
    bool topping;
    std::string toppingName;
};

class MainCourse: public MenuItem {

    public:
    // Constructor
    MainCourse(std::string n, double p, TasteProfile t, bool vegetarian = false);

    // U.G.F of MainCourse
    bool isVegetarian() const;
    // Setter
    void setVegetarian(bool v);
    // Override Virtual Func
    void printMenuItem() const override;

    std::unique_ptr<MenuItem> clone() const override {
        return std::make_unique<MainCourse>(*this);
    }

    private:
    bool vegetarian; // VEGETARIAN MENU ONERISINI SONRADAN EKLEYECEGIZ
};

class Drink: public MenuItem {

    public: 
    // Constructor
    Drink(std::string n, double p, TasteProfile t, bool carbonated = false, bool extraShot = false);

    // U.G.F of Drink
    bool isCarbonated() const;
    bool hasExtraShot() const;
    // Setter
    void setCarbonated(bool c);
    void setExtraShot(bool e);
    // Override Virtual Func
    void printMenuItem() const override;

    // Set  Drink Price
    void setDrinkPrice();
    // Adding Carbonate
    void addCarbonate();
    // Adding Extra Shot
    void addExtraShot();

    // Removing Carbonate
    void removeCarbonate();
    // Removing Extra Shot
    void removeExtraShot();

    std::unique_ptr<MenuItem> clone() const override {
        return std::make_unique<Drink>(*this);
    }

    private:
    bool carbonated;
    bool extraShot;
};

class Appetizer: public MenuItem {

    public:
    //Constructor
    Appetizer(std::string n, double p, TasteProfile t, std::string serveTime = "Before");

    // U.G.F of Appetizer
    std::string getServeTime() const;
    // Setter
    void setServeTime(std::string st);
    // Override Virtual Func
    void printMenuItem() const override;

    std::unique_ptr<MenuItem> clone() const override {
        return std::make_unique<Appetizer>(*this);
    }

    private:
    std::string serveTime; // "Before" or "After"
};

class Dessert: public MenuItem {

    public:
    //Constructor
    Dessert(std::string n, double p, TasteProfile t, bool extraChocolate = false);

    // U.G.F of Dessert
    bool hasExtraChocolate() const;
    // Setter
    void setExtraChocolate(bool ec);
    // Override Virtual Function
    void printMenuItem() const override;

    // Set Dessert Price
    void setDessertPrice();

    // Adding Extra Chocolate due to User needs
    void addExtraChocolate();

    // Removing extra chocolate 
    void removeExtraChocolate();

    std::unique_ptr<MenuItem> clone() const override {
        return std::make_unique<Dessert>(*this);
    }

    private:
    bool extraChocolate;
};

} // namespace menu

#endif // HW2_FOOD_TYPES_HPP