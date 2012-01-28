#include <string>
#include <GildedRose.h>

class SulfurasItem : public Item
{
public:
    virtual int qualityChange() {
        return 0;
    }
    SulfurasItem(std::string name, int sellIn, int quality) : Item(name, sellIn, quality) 
    {}
};

Item* Item::makeItem(std::string name, int sellIn, int quality)
{
    if(name.find("Sulfuras") != name.npos) {
        return new SulfurasItem(name, sellIn, quality);
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
    for (int i = 0; i < items.size(); i++)
    {
        if (items[i]->name != "Aged Brie" && items[i]->name != "Backstage passes to a TAFKAL80ETC concert")
        {
            if (items[i]->quality > 0)
            {
                items[i]->quality = items[i]->quality + items[i]->qualityChange();
            }
        }
        else
        {
            if (items[i]->quality < 50)
            {
                items[i]->quality = items[i]->quality + 1;
                
                if (items[i]->name == "Backstage passes to a TAFKAL80ETC concert")
                {
                    if (items[i]->sellIn < 11)
                    {
                        if (items[i]->quality < 50)
                        {
                            items[i]->quality = items[i]->quality + 1;
                        }
                    }
                    
                    if (items[i]->sellIn < 6)
                    {
                        if (items[i]->quality < 50)
                        {
                            items[i]->quality = items[i]->quality + 1;
                        }
                    }
                }
            }
        }
        
        if (items[i]->name != "Sulfuras, Hand of Ragnaros")
        {
            items[i]->sellIn = items[i]->sellIn - 1;
        }
        
        if (items[i]->sellIn < 0)
        {
            if (items[i]->name != "Aged Brie")
            {
                if (items[i]->name != "Backstage passes to a TAFKAL80ETC concert")
                {
                    if (items[i]->quality > 0)
                    {
                        if (items[i]->name != "Sulfuras, Hand of Ragnaros")
                        {
                            items[i]->quality = items[i]->quality + items[i]->qualityChange();
                        }
                    }
                }
                else
                {
                    items[i]->quality = items[i]->quality - items[i]->quality;
                }
            }
            else
            {
                if (items[i]->quality < 50)
                {
                    items[i]->quality = items[i]->quality + 1;
                }
            }
        }
    }
}
