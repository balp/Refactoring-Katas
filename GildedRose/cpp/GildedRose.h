#ifndef GILDED_ROSE_H
#define GILDED_ROSE_H

#include <string>
#include <vector>
#include <memory>

/**
 * A Basic Item.
 */
class Item
{
    public:
        std::string name;
        Item(std::string name, int sellIn, int quality) :
            name(name), m_sellIn(sellIn), m_quality(quality) {
                setQuality(m_quality); // Makes sure it's in limits
            }
        virtual ~Item() {}

        virtual int qualityChange() {
            if(m_sellIn <= 0) {
                return -2;
            }
            return -1;
        } 

        virtual int sellIn() const {
            return m_sellIn;
        }
        virtual void updateSellIn() {
            --m_sellIn;
        }
        virtual int quality() const {
            return m_quality;
        }
        virtual void setQuality(int quality);
        virtual void updateQuality() {
            setQuality( quality() + qualityChange() );
        }

    protected:
        int m_sellIn;
        int m_quality;
};

class SulfurasItem : public Item
{
    public:
        SulfurasItem(std::string name, int sellIn, int quality) :
            Item(name, sellIn, quality) {}
        virtual void updateSellIn() {}
        virtual int qualityChange() {
            return 0;
        } 
};

class BrieItem : public Item
{
    public:
        BrieItem(std::string name, int sellIn, int quality) :
            Item(name, sellIn, quality) {}
        virtual int qualityChange() {
            return +1;
        } 
};
class BackstagePassItem : public Item
{
    public:
        BackstagePassItem(std::string name, int sellIn, int quality) :
            Item(name, sellIn, quality) {}
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

std::shared_ptr<Item> makeItem(std::string name, int sellIn, int quality);


class GildedRose
{
public:
    std::vector< std::shared_ptr<Item> > items;
    GildedRose(std::vector< std::shared_ptr<Item> > items) : items (items) {}
    
    void updateQuality();

};

#endif // GILDED_ROSE_H
