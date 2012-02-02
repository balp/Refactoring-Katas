
#include <vector>
#include <Item.h>

class GildedRose
{
public:
    std::vector<Item> items;
    GildedRose(std::vector<Item> items) : items (items) 
    {}
    
    void updateQuality() ;
};

