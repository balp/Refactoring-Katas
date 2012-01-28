#include <string>
#include <GildedRose.h>

class SulfurasItem : public Item
{
public:
    virtual int qualityChange() {
        return 0;
    }
    virtual void updateSellIn() {
    }
    virtual void updateQuality() {}
    void setQuality(int quality) {}
    
    SulfurasItem(std::string name, int sellIn, int quality) : Item(name, sellIn, quality) 
    {}
};

class BrieItem : public Item
{
public:
    BrieItem(std::string name, int sellIn, int quality) : Item(name, sellIn, quality) 
    {}
    virtual int qualityChange() {
        return 1;
    }
    
};

class BackstagePassItem : public Item
{
public:
    BackstagePassItem(std::string name, int sellIn, int quality) : Item(name, sellIn, quality) 
    {}
    virtual int qualityChange() {
        if(m_sellIn > 10) {
            return 1;
        }
        if(m_sellIn > 5) {
            return 2;
        }
        if(m_sellIn > 0) {
            return 3;
        }
        if(m_sellIn == 0) {
            return -m_quality;
        }
        return 0;
    }
    
};

Item* Item::makeItem(std::string name, int sellIn, int quality)
{
    if(name.find("Backstage") != name.npos) {
        return new BackstagePassItem(name, sellIn, quality);
    }
    if(name.find("Sulfuras") != name.npos) {
        return new SulfurasItem(name, sellIn, quality);
    }
    if(name.find("Brie") != name.npos) {
        return new BrieItem(name, sellIn, quality);
    }
    return new Item(name, sellIn, quality);
}

void example()
{
    std::vector<Item*> items;
    items.push_back(Item::makeItem("+5 Dexterity Vest", 10, 20));
    items.push_back(Item::makeItem("Aged Brie", 2, 0));
    items.push_back(Item::makeItem("Elixir of the Mongoose", 5, 7));
    items.push_back(Item::makeItem("Sulfuras, Hand of Ragnaros", 0, 80));
    items.push_back(Item::makeItem("Backstage passes to a TAFKAL80ETC concert", 15, 20));
    items.push_back(Item::makeItem("Conjured Mana Cake", 3, 6));
    GildedRose app(items);
    app.updateQuality();
}

void GildedRose::updateQuality()
{
    for (std::vector<Item*>::iterator iter = items.begin();
         iter != items.end();
         ++iter)
    {
        (*iter)->updateQuality();
    }
}
