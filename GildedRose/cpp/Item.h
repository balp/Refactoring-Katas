/**
 * This is the Items class, editing this wil anger the goblin in the corner
 */
#include <string>

class Item
{
public:
    std::string name;
    int sellIn;
    int quality;
    Item(std::string name, int sellIn, int quality) : name(name), sellIn(sellIn), quality(quality) 
    {}
};

