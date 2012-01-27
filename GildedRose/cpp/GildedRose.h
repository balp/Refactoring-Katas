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
        /**
         * The name of the item.
         */
        std::string name;

        /**
         * Destructor.
         */
        virtual ~Item() {}


        /**
         * How many days until the item should be sold.
         *
         * @return A number of full days or zero if not applicable.
         */
        virtual int sellIn() const {
            return m_sellIn;
        }

        /**
         * Do the daily sel in days update.
         */
        virtual void updateSellIn() {
            --m_sellIn;
        }

        /**
         * get the currect quality of the item.
         *
         * @return a number representing the quality the higher the better
         */
        virtual int quality() const {
            return m_quality;
        }

        /**
         * Do the daily quality update.
         */
        virtual void updateQuality() {
            setQuality( quality() + qualityChange() );
        }

        /**
         * Factory for Item.
         *
         * @param name Name of the item
         * @param sellIn initial number of days to sell in.
         * @param quality initial quality number
         * @return a shared pointer to the new Item.
         */
        static std::shared_ptr<Item> makeItem(std::string name, int sellIn, int quality);
    protected:
        /**
         * Constructor.
         *
         * @param name Name of the item
         * @param sellIn initial number of days to sell in.
         * @param quality initial quality number
         */
        Item(std::string name, int sellIn, int quality) :
            name(name), m_sellIn(sellIn), m_quality(quality) {
                setQuality(m_quality); // Makes sure it's in limits
            }
        /**
         * How many days lets untill the item needs to be sold.
         */
        int m_sellIn;

        /**
         * The current quality of the item.
         */
        int m_quality;

        /**
         * Set the new quality of an item.
         *
         * @param quality the new quality
         */
        virtual void setQuality(int quality);

        /**
         * Get the change in quality for this item.
         *
         * @return How much the quality increases in one day.
         */
        virtual int qualityChange() {
            if(m_sellIn <= 0) {
                return -2;
            }
            return -1;
        } 
};

/**
 * Class for the Gilded Rose Inn Inventory.
 *
 * Keeps track of items in stock. The time to sell for each item and
 * the current quality.
 */
class GildedRose
{
public:
    /**
     * List of all items.
     */
    std::vector< std::shared_ptr<Item> > items;

    /**
     * Basic constructor.
     *
     * This fills the inventory with the items in the provided list.
     *
     * @param items A vector with items to place in the inventory.
     */
    GildedRose(std::vector< std::shared_ptr<Item> > items) : items (items) {}
    
    /**
     * Do the daily maintanance update.
     *
     * Call this function each night to make the updates.
     *
     * @note There is no protection to make sure this isn't called many times in
     * one day.
     */
    void updateQuality();

};

#endif // GILDED_ROSE_H
