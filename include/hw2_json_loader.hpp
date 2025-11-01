#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include <memory>
#include <nlohmann/json.hpp>

#include "hw2_food_types.hpp"    // tüm alt sınıflar burada
// veya ayrı ayrı: #include "hw2_menu_item.hpp"

namespace menu {

inline TasteProfile parseTaste(const nlohmann::json& t) {
    TasteProfile tp;
    tp.sweet  = t.value("sweet", 0);
    tp.sour   = t.value("sour", 0);
    tp.bitter = t.value("bitter", 0);
    tp.salty  = t.value("salty", 0);
    tp.savory = t.value("savory", 0);
    return tp;
}

// 👇 asıl fonksiyon
inline std::vector<std::unique_ptr<MenuItem>>
loadMenuFromJson(const std::string& filename)
{
    std::vector<std::unique_ptr<MenuItem>> items;

    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cerr << "Could not open menu json: " << filename << "\n";
        return items;
    }

    nlohmann::json j;
    in >> j;

    // 1) starters
    if (j.contains("starters")) {
        for (const auto& s : j["starters"]) {
            std::string name = s.value("name", "Unknown Starter");
            double price = s.value("price", 0.0);
            auto tp = parseTaste(s["taste_balance"]);
            // default: hot = false
            items.push_back(std::make_unique<Starter>(name, price, tp, false));
        }
    }

    // 2) salads
    if (j.contains("salads")) {
        for (const auto& s : j["salads"]) {
            std::string name = s.value("name", "Unknown Salad");
            double price = s.value("price", 0.0);
            auto tp = parseTaste(s["taste_balance"]);
            items.push_back(std::make_unique<Salad>(name, price, tp, false, "None"));
        }
    }

    // 3) main_courses
    if (j.contains("main_courses")) {
        for (const auto& s : j["main_courses"]) {
            std::string name = s.value("name", "Unknown Main");
            double price = s.value("price", 0.0);
            auto tp = parseTaste(s["taste_balance"]);
            // default: vegetarian = false
            items.push_back(std::make_unique<MainCourse>(name, price, tp, false));
        }
    }

    // 4) drinks
    if (j.contains("drinks")) {
        for (const auto& s : j["drinks"]) {
            std::string name = s.value("name", "Unknown Drink");
            double price = s.value("price", 0.0);
            auto tp = parseTaste(s["taste_balance"]);
            // default: carbonated = false, extraShot = false
            items.push_back(std::make_unique<Drink>(name, price, tp, false, false));
        }
    }

    // 5) appetizers
    if (j.contains("appetizers")) {
        for (const auto& s : j["appetizers"]) {
            std::string name = s.value("name", "Unknown Appetizer");
            double price = s.value("price", 0.0);
            auto tp = parseTaste(s["taste_balance"]);
            items.push_back(std::make_unique<Appetizer>(name, price, tp, "before"));
        }
    }

    // 6) desserts
    if (j.contains("desserts")) {
        for (const auto& s : j["desserts"]) {
            std::string name = s.value("name", "Unknown Dessert");
            double price = s.value("price", 0.0);
            auto tp = parseTaste(s["taste_balance"]);
            items.push_back(std::make_unique<Dessert>(name, price, tp, false));
        }
    }

    return items;
}

} // namespace menu