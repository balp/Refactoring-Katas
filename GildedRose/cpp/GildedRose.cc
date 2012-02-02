#include <string>
#include <GildedRose.h>

#include <iostream>

using namespace std;

void example()
{
    vector<Item> items;
    items.push_back(Item("+5 Dexterity Vest", 10, 20));
    items.push_back(Item("Aged Brie", 2, 0));
    items.push_back(Item("Elixir of the Mongoose", 5, 7));
    items.push_back(Item("Sulfuras, Hand of Ragnaros", 0, 80));
    items.push_back(Item("Backstage passes to a TAFKAL80ETC concert", 15, 20));
    items.push_back(Item("Conjured Mana Cake", 3, 6));
    GildedRose app(items);
    app.updateQuality();
}

class ItemRules
{
    public:
        Item* item;
        ItemRules(Item* i): item(i) { }
        virtual ~ItemRules() {}

        virtual void updateQuality() {
            if(item->quality > 0) {
                item->quality -= 1;
            }
        }

        virtual void updateSellIn() {
            item->sellIn -= 1;
        }
};

class BrieRules : public ItemRules
{
    public:
        BrieRules(Item* item) : ItemRules(item) {}
        virtual void updateQuality() {
            if(item->quality < 50) {
                item->quality += 1;
            }
        }

};

class BackstageRules : public ItemRules
{
    public:
        BackstageRules(Item* item) : ItemRules(item) {}
        virtual void updateQuality() {
            if(item->quality < 50) {
                if(item->sellIn > 10) {
                    item->quality += 1;
                } else if(item->sellIn > 5) {
                    item->quality += 2;
                } else if(item->sellIn > 0) {
                    item->quality += 3;
                }
            }
            if(item->sellIn == 0) {
                item->quality = 0;
            }
        }
};

class SulfurasRules : public ItemRules
{
    public:
        SulfurasRules(Item* item) : ItemRules(item) {}
        virtual void updateQuality() {}
        virtual void updateSellIn() {}
};

class ConjuredRules : public ItemRules
{
    public:
        ConjuredRules(Item* item) : ItemRules(item) {}
        virtual void updateQuality() {
            ItemRules::updateQuality();
            ItemRules::updateQuality();
        }
};

ItemRules* getRules(Item* item)
{
    std::string name(item->name);
    if(name.find("Conjured") != name.npos) {
        return new ConjuredRules(item);
    }
    if(name.find("Backstage") != name.npos) {
        return new BackstageRules(item);
    }
    if(name.find("Sulfuras") != name.npos) {
        return new SulfurasRules(item);
    }
    if(name.find("Brie") != name.npos) {
        return new BrieRules(item);
    }
    return new ItemRules(item);
}

void GildedRose::updateQuality() 
{
    for (std::vector<Item>::iterator iter = items.begin();
                iter != items.end();
                ++iter) {
        ItemRules* item = getRules(&(*iter));
        item->updateQuality();
        item->updateSellIn();
        if (iter->sellIn < 0)
        {
            item->updateQuality();
        }
    }
}
