// hw2_menu_item.hpp
#pragma once
#include <string>
#include <memory>

namespace menu {

struct TasteProfile {
    double sweet{};
    double sour{};
    double bitter{};
    double salty{};
    double savory{};
    void printTasteProfile() const;
};

class MenuItem {
protected:
    std::string foodName;
    double      foodPrice;
    TasteProfile balance;

public:
    MenuItem(std::string n, double p, TasteProfile t)
        : foodName(std::move(n)), foodPrice(p), balance(t) {}

    virtual ~MenuItem() = default;

    double getPrice() const { return foodPrice; }
    void setPrice(double p) { foodPrice = p; }

    TasteProfile getTasteProfile() const { return balance; }
    void setTasteProfile(const TasteProfile& t) { balance = t; }

    virtual void printMenuItem() const = 0;
    virtual std::unique_ptr<MenuItem> clone() const = 0;
};

} // namespace menu
