
#include <GildedRose.h>
#include <memory>
#include <string>

void Item::setQuality(int quality)
{
    m_quality = quality;
    if(m_quality > 50) {
        m_quality = 50;
    }
    if(m_quality < 0) {
        m_quality = 0;
    }
}

std::shared_ptr<Item> makeItem(std::string name, int sellIn, int quality)
{
    if(name.find("Backstage") != name.npos) {
        std::shared_ptr<Item> ret (new BackstagePassItem(name, sellIn, quality));
        return ret;
    }
    if(name.find("Sulfuras") != name.npos) {
        std::shared_ptr<Item> ret (new SulfurasItem(name, sellIn, quality));
        return ret;
    }
    if(name.find("Brie") != name.npos) {
        std::shared_ptr<Item> ret (new BrieItem(name, sellIn, quality));
        return ret;
    }
    std::shared_ptr<Item> ret (new Item(name, sellIn, quality));
    return ret;
}

void example()
{
    std::vector< std::shared_ptr<Item> > items;
    items.push_back(makeItem("+5 Dexterity Vest", 10, 20));
    items.push_back(makeItem("Aged Brie", 2, 0));
    items.push_back(makeItem("Elixir of the Mongoose", 5, 7));
    items.push_back(makeItem("Sulfuras, Hand of Ragnaros", 0, 80));
    items.push_back(makeItem("Backstage passes to a TAFKAL80ETC concert", 15, 20));
    items.push_back(makeItem("Conjured Mana Cake", 3, 6));
    GildedRose app(items);
    app.updateQuality();
}

void GildedRose::updateQuality()
{
    for(auto i = items.begin() ; i != items.end() ; ++i)
    {
        (*i)->updateQuality();
        (*i)->updateSellIn();
    }
}

