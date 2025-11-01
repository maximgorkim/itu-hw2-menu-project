#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <nlohmann/json.hpp>
#include "hw2_food_types.hpp"
#include "hw2_menu_item.hpp"
#include "hw2_user_menu.hpp"



namespace menu {

    // -----------TasteProfile Methods----------- //
    void TasteProfile::printTasteProfile() const {
    std::cout << "[sweet:" << sweet
              << " sour:" << sour
              << " bitter:" << bitter
              << " salty:" << salty
              << " savory:" << savory
              << "]";
}

    // -----------Starter Methods----------- //
    Starter::Starter(std::string n, double p, TasteProfile t, bool hot)
    : MenuItem(n, p, t), hot(hot) {}
    
    bool Starter::isHot() const {return hot;}    
    
    void Starter::printMenuItem() const{
        std::cout << "Starter: " << foodName 
                  << " | Price: $" << foodPrice 
                  << " | Taste Profile: ";
        balance.printTasteProfile();
        std::cout << " | Hot: " << (hot ? "Yes" : "No") 
                  << std::endl;
    }

    void Starter::setHot(bool h) {hot = h;} 


    // -----------Salad Methods----------- //
    Salad::Salad(std::string n, double p, TasteProfile t, bool topping, std::string toppingName)
    : MenuItem(n, p, t), topping{topping}, toppingName{toppingName} {}

    bool Salad::hasTopping() const {return topping;}
    std::string Salad::getToppingName() const {return toppingName;}

    void Salad::setTopping(bool t) {topping = t;}

    void Salad::setToppingName( const std::string& tn) {toppingName = tn;}

    void Salad::printMenuItem() const {
        std::cout << "Salad: " << foodName 
                  << " | Price: $" << foodPrice 
                  << " | Taste Profile: ";
        balance.printTasteProfile();
        std::cout << " | Topping: " << (topping ? toppingName : "No Topping") 
                  << std::endl;
    }

    void Salad::setSaladPrice() {
        double basePrice = getPrice();
        double finalPrice = basePrice;
        if(topping) {
            finalPrice += 2.25;
        }
        else {
            finalPrice -= 2.25;
        }
        setPrice(finalPrice);
    }
    
    void Salad::addTopping(const std::string& tn) {
        if(topping) {
            std::cout << "You've already added topping." << std::endl;
            return;
        }
        topping = true;
        toppingName = tn;
        setSaladPrice();
        std::cout << toppingName << " topping added successfully." << std::endl;
    }

    void Salad::removeTopping() {
        if(!topping) {
            std::cout << "There isn't any topping to remove." << std::endl;
            return;
        }
        topping = false;
        toppingName = "None";
        setSaladPrice();
        std::cout << "Topping removed successfully." << std::endl;
    }


    // -----------Main Course Methods----------- //
    MainCourse::MainCourse(std::string n, double p, TasteProfile t, bool vegetarian)
    : MenuItem(n, p, t), vegetarian{vegetarian} {}

    bool MainCourse::isVegetarian() const {return vegetarian;}

    void MainCourse::setVegetarian(bool v) {vegetarian = v;}

    void MainCourse::printMenuItem() const {
        std::cout << "Main Course: " << foodName 
                  << " | Price: $" << foodPrice 
                  << " | Taste Profile: ";
        balance.printTasteProfile();
        std::cout << " | Vegetarian: " << (vegetarian ? "Yes" : "No") 
                  << std::endl;
    }


    //-----------Drink Methods----------- //
    Drink::Drink(std::string n, double p, TasteProfile t, bool carbonated, bool extraShot)
    : MenuItem(n, p, t), carbonated{carbonated}, extraShot{extraShot} {}

    bool Drink::isCarbonated() const {return carbonated;}

    bool Drink::hasExtraShot() const {return extraShot;}

    void Drink::setCarbonated(bool c) {carbonated = c;}
    void Drink::setExtraShot(bool e) {extraShot = e;}

    void Drink::printMenuItem() const {
        std::cout << "Drink: " << foodName 
                  << " | Price: $" << foodPrice 
                  << " | Taste Profile: ";
        balance.printTasteProfile();
        std::cout << " | Carbonated: " << (carbonated ? "Yes" : "No") 
                  << " | Extra Shot: " << (extraShot ? "Yes" : "No") 
                  << std::endl;
    }

    void Drink::setDrinkPrice() {
        double basePrice = getPrice();
        double finalPrice = basePrice;
        if(carbonated) {
            finalPrice += 0.5;
        }
        else if(!carbonated) {
            finalPrice -= 0.5;
        }
        if(extraShot) {
            finalPrice += 2.5;
        }
        else if(!extraShot) {
            finalPrice -= 2.5;
        }
        setPrice(finalPrice);
    }

    void Drink::addCarbonate() {
        if(carbonated) {
            std::cout << "You've already added carbonate." << std::endl;
            return;
        }
        carbonated = true;
        setDrinkPrice();
        std::cout << "Carbonate added successfully." << std::endl;
    }

    void Drink::addExtraShot() {
        if(extraShot) {
            std::cout << "You've already added extra shot." << std::endl;
            return;
        }
        extraShot = true;
        setDrinkPrice();
        std::cout << "Extra shot added successfully." << std::endl;
    }

    void Drink::removeCarbonate() {
        if(!carbonated) {
            std::cout << "There isn't any carbonate to remove." << std::endl;
            return;
        }
        carbonated = false;
        setDrinkPrice();
        std::cout << "Carbonate removed successfully." << std::endl;
    }

    void Drink::removeExtraShot() {
        if(!extraShot) {
            std::cout << "There isn't any extra shot to remove." << std::endl;
            return;
        }
        extraShot = false;
        setDrinkPrice();
        std::cout << "Extra shot removed successfully." << std::endl;
    }

    //-----------Appetizer Methods----------- //
    Appetizer::Appetizer(std::string n, double p, TasteProfile t, std::string serveTime)
    : MenuItem(n, p, t), serveTime{serveTime} {}

    std::string Appetizer::getServeTime() const {return serveTime;}

    void Appetizer::setServeTime(std::string st) {serveTime = st;}

    void Appetizer::printMenuItem() const {
        std::cout << "Appetizer: " << foodName 
                  << " | Price: $" << foodPrice 
                  << " | Taste Profile: ";
        balance.printTasteProfile();
        std::cout << " | Serve Time: " << serveTime 
                  << std::endl;
    }


    //-----------Dessert Methods----------- //
    Dessert::Dessert(std::string n, double p, TasteProfile t, bool extraChocolate)
    : MenuItem(n, p, t), extraChocolate{extraChocolate} {}

    bool Dessert::hasExtraChocolate() const {return extraChocolate;}
    
    void Dessert::setExtraChocolate(bool ec) {extraChocolate = ec;}
    
    void Dessert::printMenuItem() const {
        std::cout << "Dessert: " << foodName 
                  << " | Price: $" << foodPrice 
                  << " | Taste Profile: ";
        balance.printTasteProfile();
        std::cout << " | Extra Chocolate: " << (extraChocolate ? "Yes" : "No") 
                  << std::endl;
    }

    void Dessert::setDessertPrice() {
        double basePrice = getPrice();
        double finalPrice = basePrice;
        if(extraChocolate) {
            finalPrice += 1.5;
        }
        else {
            finalPrice -= 1.5;
        }
        setPrice(finalPrice);
    }

    void Dessert::addExtraChocolate() {
        if(extraChocolate) {
            std::cout << "You've already added extra chocolate." << std::endl;
            return;
        }
        extraChocolate = true;
        setDessertPrice();
        std::cout << "Extra chocolate added successfully." << std::endl;
    }

    void Dessert::removeExtraChocolate() {
        if(!extraChocolate) {
            std::cout << "There isn't any extra chocolate to remove." << std::endl;
            return;
        }
        extraChocolate = false;
        setDessertPrice();
        std::cout << "Extra chocolate removed successfully." << std::endl;
    }


    // ---------------------- //
    // Menu methods           //
    // ---------------------- //
    Menu::Menu(double totalCost, TasteProfile avgTaste, std::vector<std::unique_ptr<MenuItem>>&& menuItems)
        : totalCost{totalCost}, avgTaste{avgTaste}, menuItems{std::move(menuItems)} {}

    TasteProfile Menu::averageTasteProfileOfMenu() const {
    TasteProfile acc{0,0,0,0,0};
    if (menuItems.empty()) return acc;

    for (const auto& item : menuItems) {
        TasteProfile tp = item->getTasteProfile();
        acc.sweet  += tp.sweet;
        acc.sour   += tp.sour;
        acc.bitter += tp.bitter;
        acc.salty  += tp.salty;
        acc.savory += tp.savory;
    }

    double count = static_cast<double>(menuItems.size());
    acc.sweet  /= count;
    acc.sour   /= count;
    acc.bitter /= count;
    acc.salty  /= count;
    acc.savory /= count;

    return acc;
    }
    
    void Menu::addItem(std::unique_ptr<MenuItem> mi) {
        menuItems.push_back(std::move(mi));
        std::cout << "Item added successfully." << std::endl;
    }

    bool Menu::removeItem(std::size_t index) {
        if(index >= menuItems.size()) {
            std::cout << "Invalid index." << std::endl;
            return false;
        }
        menuItems.erase(menuItems.begin() + index);
        std::cout << "Item removed successfully." << std::endl;
        return true;
    }

    bool Menu::updateTasteProfileOfMenuItem(std::size_t index, double increment) {
        if(index >= menuItems.size()) {return false;}
        TasteProfile t = menuItems[index]->getTasteProfile();
        int choice;
        
        std::cout << "\nChoose which taste to increase:\n"
          << "1. Sweet\n"
          << "2. Sour\n"
          << "3. Bitter\n"
          << "4. Salty\n"
          << "5. Savory\n"
          << "0. Cancel\n"
          << "Enter your choice: ";

        std::cin>> choice;
        switch(choice) {
            case 1: 
                t.sweet += increment;
                break;
            case 2:
                t.sour += increment;
                break;
            case 3:
                t.bitter += increment;
                break;
            case 4:
                t.salty += increment;
                break;
            case 5:
                t.savory += increment;
                break;
            case 0:
                return false;
        }
        menuItems[index]->setTasteProfile(t);
        std::cout << "Taste Profile Of Menu Item Updated Successfully." << std::endl;
        return true;
    }

    double Menu::getTotalCost() {
    double sum = 0.0;
    for (const auto& item : menuItems) {
        sum += item->getPrice();
    }
    totalCost = sum;
    return totalCost;
    }

    void Menu::printMenu() const {
    const_cast<Menu*>(this)->getTotalCost();
    std::cout << "----- USER MENU -----\n";
    for (std::size_t i = 0; i < menuItems.size(); ++i) {
        std::cout << "#" << i << " ";
        menuItems[i]->printMenuItem();
    }
    std::cout << "Total cost: $" << totalCost << "\n";
    std::cout << "Avg taste balance: ";
    averageTasteProfileOfMenu().printTasteProfile();
    std::cout << "\n---------------------\n";
    }



    // ---------------------- //
    // User methods           //
    // ---------------------- //
    User::User(const std::string& name, const std::string& surname, const std::string& gender)
    : userName{name}, userSurname{surname}, userGender{gender}, userMenu() {}
    User::User(const std::string& userName, const std::string& userSurname, const std::string& userGender, Menu&& userMenu)
    : userName{userName}, userSurname{userSurname}, userGender{userGender}, userMenu{std::move(userMenu)} {}

    void User::getUserInfo() const {
        std::cout << " User: " << userGender << " " << userName << " " << userSurname << std::endl;
    }

    const Menu& User::getUserMenu() const {
        return userMenu;
    }

} // namespace menu



