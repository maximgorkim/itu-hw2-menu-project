#include <cstdlib>      // std::rand
#include <ctime>        // std::time
#include <limits>       // std::numeric_limits
#include <cmath>        // std::abs
#include <algorithm>    // std::min_element
#include "hw2_recommender.hpp"


#include "hw2_menu_item.hpp"   // önce MenuItem ve TasteProfile
#include "hw2_food_types.hpp"  // sonra ondan türeyenler
#include "hw2_user_menu.hpp" 



namespace recommender {

// ---------------------------
// 1. Tat uzaklığı
// ---------------------------
double tasteDistance(const menu::TasteProfile& a,
                     const menu::TasteProfile& b)
{
    // basit L1 (manhattan) uzaklığı
    double d = 0.0;
    d += std::abs(a.sweet  - b.sweet);
    d += std::abs(a.sour   - b.sour);
    d += std::abs(a.bitter - b.bitter);
    d += std::abs(a.salty  - b.salty);
    d += std::abs(a.savory - b.savory);
    return d;
}

// ---------------------------
// 2. Dengeli profil
// ---------------------------
menu::TasteProfile balancedTasteProfile() {
    // PDF "balanced" deyince aslında ortalamaya yakın bir şey istiyor
    // biz basit tutup hepsini 5 yapıyoruz
    return menu::TasteProfile{5,5,5,5,5};
}

// ---------------------------
// yardımcı: item'leri kategoriye ayır
// ---------------------------
struct Buckets {
    std::vector<const menu::MenuItem*> starters;
    std::vector<const menu::MenuItem*> salads;
    std::vector<const menu::MenuItem*> mains;
    std::vector<const menu::MenuItem*> drinks;
    std::vector<const menu::MenuItem*> apps;
    std::vector<const menu::MenuItem*> desserts;
};

static Buckets bucketize(
    const std::vector<std::unique_ptr<menu::MenuItem>>& allItems)
{
    Buckets b;
    for (const auto& up : allItems) {
        const menu::MenuItem* item = up.get();

        // dynamic_cast ile türü çıkarıyoruz
        if (dynamic_cast<const menu::Starter*>(item)) {
            b.starters.push_back(item);
        } else if (dynamic_cast<const menu::Salad*>(item)) {
            b.salads.push_back(item);
        } else if (dynamic_cast<const menu::MainCourse*>(item)) {
            b.mains.push_back(item);
        } else if (dynamic_cast<const menu::Drink*>(item)) {
            b.drinks.push_back(item);
        } else if (dynamic_cast<const menu::Appetizer*>(item)) {
            b.apps.push_back(item);
        } else if (dynamic_cast<const menu::Dessert*>(item)) {
            b.desserts.push_back(item);
        }
    }
    return b;
}

// ---------------------------
// yardımcı: random pick
// ---------------------------
template <typename T>
static const T* pickRandom(const std::vector<const T*>& v)
{
    if (v.empty()) return nullptr;
    int idx = std::rand() % v.size();
    return v[idx];
}

// ---------------------------
// 3. Random menü
// ---------------------------
menu::Menu makeRandomMenu(
    const std::vector<std::unique_ptr<menu::MenuItem>>& allItems)
{
    // 1) kategorilere ayır
    Buckets b = bucketize(allItems);

    // 2) rastgele tohum
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    menu::Menu m;

    // 3) her kategoriden 1 tane seç ve menüye ekle
    auto addIf = [&](const menu::MenuItem* it){
        if (!it) return;
        // burada clone kullandık, çünkü elimizde sadece const MenuItem* var
        m.addItem(it->clone());
    };

    addIf(pickRandom(b.starters));
    addIf(pickRandom(b.salads));
    addIf(pickRandom(b.mains));
    addIf(pickRandom(b.drinks));
    addIf(pickRandom(b.apps));
    addIf(pickRandom(b.desserts));

    // toplam maliyeti güncelle
    m.getTotalCost();
    return m;
}

// ---------------------------
// 4. Taste profile'a göre menü
// ---------------------------
menu::Menu makeMenuForTasteProfile(
    const std::vector<std::unique_ptr<menu::MenuItem>>& allItems,
    const menu::TasteProfile& target)
{
    Buckets b = bucketize(allItems);
    menu::Menu m;

    auto pickClosest = [&](const std::vector<const menu::MenuItem*>& vec) -> const menu::MenuItem* {
        if (vec.empty()) return nullptr;
        const menu::MenuItem* best = nullptr;
        double bestDist = std::numeric_limits<double>::max();
        for (const auto* it : vec) {
            double d = tasteDistance(it->getTasteProfile(), target);
            if (d < bestDist) {
                bestDist = d;
                best = it;
            }
        }
        return best;
    };

    auto addIf = [&](const menu::MenuItem* it){
        if (!it) return;
        m.addItem(it->clone());
    };

    addIf(pickClosest(b.starters));
    addIf(pickClosest(b.salads));
    addIf(pickClosest(b.mains));
    addIf(pickClosest(b.drinks));
    addIf(pickClosest(b.apps));
    addIf(pickClosest(b.desserts));

    m.getTotalCost();
    return m;
}

} // namespace recommender
