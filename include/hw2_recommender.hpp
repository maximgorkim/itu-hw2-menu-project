#if !defined(HW2_RECOMMENDER_HPP)
#define HW2_RECOMMENDER_HPP

#pragma once

#include <vector>
#include <memory>
#include "hw2_menu_item.hpp"    
#include "hw2_food_types.hpp"   

namespace menu {
    class Menu;
    struct TasteProfile;
}    


namespace recommender {


double tasteDistance(const menu::TasteProfile& a,
                     const menu::TasteProfile& b);


menu::TasteProfile balancedTasteProfile();


menu::Menu makeRandomMenu(
    const std::vector<std::unique_ptr<menu::MenuItem>>& allItems);


menu::Menu makeMenuForTasteProfile(
    const std::vector<std::unique_ptr<menu::MenuItem>>& allItems,
    const menu::TasteProfile& target);

} // namespace recommender

#endif // HW2_RECOMMENDER_HPP