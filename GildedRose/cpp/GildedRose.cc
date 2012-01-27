
#include <GildedRose.h>
#include <memory>
#include <string>

/**
 * Subclass for the Sulfuras Items.
 *
 * These legendary items does decrease in quality over time,
 * so sellIn and quality never changes.
 */
class SulfurasItem : public Item
{
    public:
        /**
         * The constructor.
         */
        SulfurasItem(std::string name, int sellIn, int quality) :
            Item(name, sellIn, quality) {}
        virtual void updateSellIn() {}
    protected:
        virtual int qualityChange() {
            return 0;
        } 
};

/**
 * Class for Aged Brie.
 *
 * Storing Brie actually makes it become better over time.
 */
class BrieItem : public Item
{
    public:
        /**
         * Constructor.
         */
        BrieItem(std::string name, int sellIn, int quality) :
            Item(name, sellIn, quality) {}
    protected:
        virtual int qualityChange() {
            return +1;
        } 
};

/**
 * Class for the backstage passes.
 *
 * Backstage passes increaes quality until the consert,
 * but after the consert they are useless.
 */
class BackstagePassItem : public Item
{
    public:
        /**
         * Constrctor
         */
        BackstagePassItem(std::string name, int sellIn, int quality) :
            Item(name, sellIn, quality) {}
    protected:
        virtual int qualityChange() {
            if(m_sellIn <= 0) {
                return -m_quality;
            }
            if(m_sellIn <= 5) {
                return +3;
            }
            if(m_sellIn <= 10) {
                return +2;
            }
            return +1;
        } 
};



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

std::shared_ptr<Item> Item::makeItem(std::string name, int sellIn, int quality)
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
    for(auto i = items.begin() ; i != items.end() ; ++i)
    {
        (*i)->updateQuality();
        (*i)->updateSellIn();
    }
}

