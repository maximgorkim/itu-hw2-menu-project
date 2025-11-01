#include <iostream>
#include <vector>
#include <memory>

#include "hw2_json_loader.hpp"     // loadMenuFromJson(...)
#include "hw2_recommender.hpp"     // makeRandomMenu, makeMenuForTasteProfile
#include "hw2_menu_item.hpp"       // MenuItem, TasteProfile
#include "hw2_user_menu.hpp"       // User, Menu
#include "hw2_food_types.hpp"      // Starter, Salad, MainCourse, Drink, Appetizer, Dessert

int main() {
    using namespace menu;

    std::cout << "=== Restaurant Bot ===\n";
    std::cout << "I'll create menus for you based on your preferences.\n\n";

    // 1) GET USER INFO
    std::string name, surname, gender;
    std::cout << "First name: ";
    std::cin >> name;
    std::cout << "Last name: ";
    std::cin >> surname;

    // gender sadece Mr / Mrs olsun
    while (true) {
        std::cout << "Gender (Mr / Mrs): ";
        std::cin >> gender;
        if (gender == "Mr" || gender == "Mrs") {
            break;
        }
        std::cout << "Only 'Mr' or 'Mrs' is allowed. Please try again.\n";
    }

    // 2) Create User
    User user{name, surname, gender};

    // 3) LOAD ALL MENU ITEMS FROM JSON
    auto allItems = loadMenuFromJson("menu_copy.json");
    if (allItems.empty()) {
        std::cerr << "Menu could not be loaded from JSON.\n";
        return 1;
    }

    int choice = -1;
    while (choice != 0) {
        std::cout << "\n--- MAIN MENU ---\n";
        std::cout << "1. Show my menu\n";
        std::cout << "2. Add / remove / update item\n";
        std::cout << "3. Create RANDOM menu\n";
        std::cout << "4. Create menu for TASTE PROFILE\n";
        std::cout << "0. Exit\n";

        // güvenli seçim
        std::cout << "Your choice (0-4): ";
        std::cin >> choice;

        if (std::cin.fail()) {
            // yanlış tip girildiyse (mesela harf)
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Invalid input. Please enter a number between 0 and 4.\n";
            continue;
        }

        if (choice < 0 || choice > 4) {
            std::cout << "Invalid choice. Please enter a number between 0 and 4.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                user.getUserMenu().printMenu();
                break;
            }
            case 2: {
                // küçük alt menü
                int sub = -1;
                while (sub != 0) {
                    std::cout << "\n--- EDIT MENU ---\n";
                    std::cout << "1. Show my menu\n";
                    std::cout << "2. Remove item by index\n";
                    std::cout << "3. Update taste of item\n";
                    std::cout << "0. Back\n";
                    std::cout << "Your choice: ";
                    std::cin >> sub;

                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(1000, '\n');
                        std::cout << "Invalid input.\n";
                        continue;
                    }

                    if (sub == 1) {
                        user.getUserMenu().printMenu();
                    } else if (sub == 2) {
                        std::size_t idx;
                        std::cout << "Enter index to remove: ";
                        std::cin >> idx;
                        // burada user'ın menüsüne non-const erişmek için
                        // getUserMenu()'nün non-const versiyonuna ihtiyacın var
                        // eğer yoksa User tarafına:
                        // Menu& getUserMenu();
                        // eklemen lazım.
                        Menu& um = const_cast<Menu&>(user.getUserMenu());
                        um.removeItem(idx);
                    } else if (sub == 3) {
                        std::size_t idx;
                        std::cout << "Enter index to update taste: ";
                        std::cin >> idx;
                        double inc;
                        std::cout << "Increment (e.g. 1): ";
                        std::cin >> inc;
                        Menu& um = const_cast<Menu&>(user.getUserMenu());
                        um.updateTasteProfileOfMenuItem(idx, inc);
                    } else if (sub == 0) {
                        break;
                    } else {
                        std::cout << "Invalid.\n";
                    }
                }
                break;
            }
            case 3: {
                auto m = recommender::makeRandomMenu(allItems);
                std::cout << "\nRandom menu created:\n";
                m.printMenu();

                // kullanıcıya sor, kaydedelim mi
                char save;
                std::cout << "Save this as your current menu? (y/n): ";
                std::cin >> save;
                if (save == 'y' || save == 'Y') {
                    // User'ı yeniden oluşturmak yerine direkt move edebilirsin
                    user = User{name, surname, gender, std::move(m)};
                    std::cout << "Menu saved.\n";
                }
                break;
            }
            case 4: {
                TasteProfile target;
                std::cout << "Enter sweet (0-10): ";  std::cin >> target.sweet;
                std::cout << "Enter sour (0-10): ";   std::cin >> target.sour;
                std::cout << "Enter bitter (0-10): "; std::cin >> target.bitter;
                std::cout << "Enter salty (0-10): ";  std::cin >> target.salty;
                std::cout << "Enter savory (0-10): "; std::cin >> target.savory;

                auto m = recommender::makeMenuForTasteProfile(allItems, target);
                std::cout << "\nMenu for your taste profile:\n";
                m.printMenu();

                char save;
                std::cout << "Save this as your current menu? (y/n): ";
                std::cin >> save;
                if (save == 'y' || save == 'Y') {
                    user = User{name, surname, gender, std::move(m)};
                    std::cout << "Menu saved.\n";
                }
                break;
            }
            case 0: {
                std::cout << "Goodbye!\n";
                break;
            }
        }
    }

    return 0;
}
