
#include <vector>
#include <gtest/gtest.h>
#include <GildedRose.h>

/*
 * Basic Requirements:
 *
 * (#1) All items have a SellIn value which denotes the number of days we have
 *      to sell the item
 * (#2) All items have a Quality value which denotes how valuable the item is
 * (#3) At the end of each day our system lowers both values for every item
 * (#4) Once the sell by date has passed, Quality degrades twice as fast
 * (#5) The Quality of an item is never negative
 * (#6) "Aged Brie" actually increases in Quality the older it gets
 * (#7) The Quality of an item is never more than 50
 * (#8) "Sulfuras", being a legendary item, never has to be sold or decreases in
 *      Quality
 * (#9) "Backstage passes", like aged brie, increases in Quality as it's SellIn
 *      value approaches; Quality increases by 2 when there are 10 days or less
 *      and by 3 when there are 5 days or less but Quality drops to 0 after the
 *      concert
 *
 * New Requirements:
 *
 * (#10) "Conjured" items degrade in Quality twice as fast as normal items
 */

/**
 * Test fixture for the GildedRose class.
 *
 * This class sets up the basic items in the shop system.
 */
class GildedRoseTests : public ::testing::Test {
    protected:
        std::vector<Item> items;
        GildedRose* app;

        virtual void SetUp() {
            items.push_back(Item("Foo", 1, 3));
            items.push_back(Item("+5 Dexterity Vest", 10, 20));
            items.push_back(Item("Aged Brie", 2, 0));
            items.push_back(Item("Elixir of the Mongoose", 5, 7));
            items.push_back(Item("Sulfuras, Hand of Ragnaros", 0, 80));
            items.push_back(Item("Backstage passes to a TAFKAL80ETC concert", 15, 20));
            items.push_back(Item("Conjured Mana Cake", 3, 6));
            app = new GildedRose(items);
        }

        virtual void TearDown() {
            delete app;
        }
};
/**
 * Test that items have a name, expected from customer but no requierment.
 */
TEST_F(GildedRoseTests, HaveName) {
    EXPECT_EQ("Foo", app->items[0].name);
}

/**
 * Requirement #1:
 * Make sure the item have a sellIn field.
 */
TEST_F(GildedRoseTests, HaveSellIn) {
    EXPECT_EQ(1, app->items[0].sellIn);
}

/**
 * Requirement #2:
 * Make sure the item have a quality field.
 */
TEST_F(GildedRoseTests, HaveQuality) {
    EXPECT_EQ(3, app->items[0].quality);
}

/**
 * Requirement #3:
 * Make sure sellIn lowers at the end of the day.
 */
TEST_F(GildedRoseTests, MakeSureSellInLowersOne) {
    EXPECT_EQ(1, app->items[0].sellIn);
    app->updateQuality();
    EXPECT_EQ(0, app->items[0].sellIn);
}

/**
 * Requirement #3:
 * Make sure quality lowers at the end of the day.
 */
TEST_F(GildedRoseTests, MakeSureQualityInLowersOne) {
    EXPECT_EQ(3, app->items[0].quality);
    app->updateQuality();
    EXPECT_EQ(2, app->items[0].quality);
}

/**
 * Requirement #4:
 * Make sure quality lowers dublle speed after sellIn < 0
 */
TEST_F(GildedRoseTests, MakeSureQualityLowersTwiceAsFast) {
    EXPECT_EQ(3, app->items[0].quality);
    app->updateQuality();
    EXPECT_EQ(0, app->items[0].sellIn); // Make sure we have the right item
    app->updateQuality();
    EXPECT_EQ(0, app->items[0].quality);
}

/**
 * Requirement #5:
 * Make sure quality never gets below 0
 *
 * We limit this to update for now, no getters or setters in the interface
 */
TEST_F(GildedRoseTests, MakeSureQualityAboveZero) {
    EXPECT_EQ(3, app->items[0].quality);
    app->updateQuality();
    EXPECT_EQ(2, app->items[0].quality); 
    app->updateQuality();
    EXPECT_EQ(0, app->items[0].quality);
    app->updateQuality();
    EXPECT_EQ(0, app->items[0].quality);
}

/**
 * Requirement #6:
 * "Aged Brie" should incread quality over time
 *
 * We limit this to update for now, no getters or setters in the interface
 */
TEST_F(GildedRoseTests, MakeSureBrieAddsToQuality) {
    EXPECT_EQ("Aged Brie", app->items[2].name);
    EXPECT_EQ(0, app->items[2].quality);
    app->updateQuality();
    EXPECT_EQ(1, app->items[2].quality); 
}

/**
 * Requirement #7:
 * Quality <= 50
 *
 * We limit this to update for now, no getters or setters in the interface
 */
TEST_F(GildedRoseTests, MakeSureQualityLessThanFifty) {
    EXPECT_EQ("Aged Brie", app->items[2].name);
    EXPECT_EQ(0, app->items[2].quality);
    for(int i = 1; i < 50 ; ++i) {
        app->updateQuality();
    }
    EXPECT_EQ(50, app->items[2].quality); 
    app->updateQuality();
    EXPECT_EQ(50, app->items[2].quality); 
}

/**
 * Requirement #8:
 * Sulfuras should not lower sellIn
 *
 */
TEST_F(GildedRoseTests, MakeSureSulfrasKeepsSellIn) {
    EXPECT_EQ("Sulfuras, Hand of Ragnaros", app->items[4].name);
    EXPECT_EQ(0, app->items[4].sellIn);
    app->updateQuality();
    EXPECT_EQ(0, app->items[4].sellIn);
}

/**
 * Requirement #8:
 * Sulfuras should keep quality
 *
 */
TEST_F(GildedRoseTests, MakeSureSulfrasKeepsQuality) {
    EXPECT_EQ("Sulfuras, Hand of Ragnaros", app->items[4].name);
    EXPECT_EQ(80, app->items[4].quality);
    app->updateQuality();
    EXPECT_EQ(80, app->items[4].quality);
}

/**
 * Requirement #9:
 * "Backstage passes", sellIn > 10 => quality += 1
 *
 */
TEST_F(GildedRoseTests, MakeSureBackstagePassAddsQuality) {
    EXPECT_EQ("Backstage passes to a TAFKAL80ETC concert", app->items[5].name);
    EXPECT_EQ(20, app->items[5].quality);
    EXPECT_EQ(15, app->items[5].sellIn);
    app->updateQuality();
    EXPECT_EQ(21, app->items[5].quality);
}

/**
 * Requirement #9:
 * "Backstage passes", sellIn < 10 => quality += 2
 *
 */
TEST_F(GildedRoseTests, MakeSureBackstagePassAddsQualityTenDays) {
    EXPECT_EQ("Backstage passes to a TAFKAL80ETC concert", app->items[5].name);
    EXPECT_EQ(20, app->items[5].quality);
    EXPECT_EQ(15, app->items[5].sellIn);
    for(int i = 0 ; i < 5 ; ++i) {
        app->updateQuality();
    }
    EXPECT_EQ(10, app->items[5].sellIn);
    EXPECT_EQ(25, app->items[5].quality);
    app->updateQuality();
    EXPECT_EQ(9, app->items[5].sellIn);
    EXPECT_EQ(27, app->items[5].quality);
}

/**
 * Requirement #9:
 * "Backstage passes", sellIn < 5 => quality += 3
 *
 */
TEST_F(GildedRoseTests, MakeSureBackstagePassAddsQualityFiveDays) {
    EXPECT_EQ("Backstage passes to a TAFKAL80ETC concert", app->items[5].name);
    EXPECT_EQ(20, app->items[5].quality);
    EXPECT_EQ(15, app->items[5].sellIn);
    for(int i = 0 ; i < 10 ; ++i) {
        app->updateQuality();
    }
    EXPECT_EQ(5, app->items[5].sellIn);
    EXPECT_EQ(35, app->items[5].quality);
    app->updateQuality();
    EXPECT_EQ(4, app->items[5].sellIn);
    EXPECT_EQ(38, app->items[5].quality);
}

/**
 * Requirement #9:
 * "Backstage passes", sellIn == 0 => quality == 0
 *
 */
TEST_F(GildedRoseTests, MakeSureBackstagePassAddsQualityAfterConcert) {
    EXPECT_EQ("Backstage passes to a TAFKAL80ETC concert", app->items[5].name);
    EXPECT_EQ(20, app->items[5].quality);
    EXPECT_EQ(15, app->items[5].sellIn);
    for(int i = 0 ; i < 15 ; ++i) {
        app->updateQuality();
    }
    EXPECT_EQ(0, app->items[5].sellIn);
    EXPECT_EQ(50, app->items[5].quality);
    app->updateQuality();
    EXPECT_EQ(-1, app->items[5].sellIn);
    EXPECT_EQ(0, app->items[5].quality);
}

/**
 * Requirement #10:
 * See that a Conjured item degrade twice as fast
 */
TEST_F(GildedRoseTests, DISABLED_MakeSureConjuredDegradeFaster) {
    EXPECT_EQ("Conjured Mana Cake", app->items[6].name);
    EXPECT_EQ(3, app->items[6].sellIn);
    EXPECT_EQ(6, app->items[6].quality);
    app->updateQuality();
    EXPECT_EQ(4, app->items[6].quality);
}
