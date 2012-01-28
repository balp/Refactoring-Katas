
#include <vector>
#include <string>


class Item
{
public:
    std::string name;
    int sellIn;
    int quality;
    
    static Item* makeItem(std::string name, int sellIn, int quality);
    
    virtual int qualityChange() {
        return -1;
    }
    
protected:
    Item(std::string name, int sellIn, int quality) : name(name), sellIn(sellIn), quality(quality) 
    {}
    
};

class GildedRose
{
public:
    std::vector<Item*> items;
    GildedRose(std::vector<Item*> items) : items (items) 
    {}
    
    void updateQuality() ;
};

