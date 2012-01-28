
#include <vector>
#include <string>


class Item
{
protected:
    std::string m_name;
    int m_sellIn;
    int m_quality;
    Item(std::string name, int sellIn, int quality) : m_name(name), m_sellIn(sellIn), m_quality(quality) 
    {}
    virtual int qualityChange() {
        if (m_sellIn <= 0) {
            return -2;
        }
        return -1;
    }  
    
public:
    const std::string& name() {
        return m_name;
    }
    
    static Item* makeItem(std::string name, int sellIn, int quality);
    
    
    virtual void updateQuality() {
        setQuality(m_quality + qualityChange());
    }
    
    virtual void updateSellIn() {
        m_sellIn -= 1;
    }
    
    int quality() {
        return m_quality;
    }
    
    int sellIn() {
        return m_sellIn;
    }
    
    void setQuality(int quality) {
        m_quality = quality;
        if(m_quality <= 0) {
            m_quality = 0;
        }
        if (m_quality >= 50) {
            m_quality = 50;
        }
    }
    
  
};

class GildedRose
{
public:
    std::vector<Item*> items;
    GildedRose(std::vector<Item*> items) : items (items) 
    {}
    
    void updateQuality() ;
};

