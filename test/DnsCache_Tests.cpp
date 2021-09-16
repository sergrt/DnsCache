// DnsCache class tests

#include "gtest/gtest.h"

#include "DnsCache.h"

TEST(DnsCache, Construct_Valid) {
    EXPECT_NO_THROW(DnsCache(10));
}

TEST(DnsCache, Construct_Invalid) {
    EXPECT_THROW(DnsCache(0), std::runtime_error);
}

TEST(DnsCache_resolve, Resolve_Empty_Valid) {
    DnsCache cache(10);
    EXPECT_TRUE(cache.resolve("something").empty());
}

TEST(DnsCache_resolve, Resolve_Empty_Invalid) {
    DnsCache cache(10);
    EXPECT_THROW(cache.resolve(""), std::runtime_error);
}

TEST(DnsCache_resolve_update, Resolve_NonEmpty_Valid_NoResult) {
    DnsCache cache(10);
    cache.update("name1", "addr1");
    EXPECT_TRUE(cache.resolve("something").empty());

    cache.update("name2", "addr2");
    EXPECT_TRUE(cache.resolve("something").empty());
}

TEST(DnsCache_resolve_update, Resolve_NonEmpty_Valid_Result) {
    DnsCache cache(10);
    cache.update("name1", "addr1");
    EXPECT_EQ(cache.resolve("name1"), "addr1");

    cache.update("name2", "addr2");
    EXPECT_EQ(cache.resolve("name2"), "addr2");
}

TEST(DnsCache_update, Update_Record) {
    DnsCache cache(10);
    cache.update("name1", "addr1");
    cache.update("name2", "addr2");
    cache.update("name3", "addr3");

    cache.update("name3", "addrA");
    EXPECT_EQ(cache.resolve("name1"), "addr1");
    EXPECT_EQ(cache.resolve("name2"), "addr2");
    EXPECT_EQ(cache.resolve("name3"), "addrA");

    cache.update("name2", "addrB");
    EXPECT_EQ(cache.resolve("name1"), "addr1");
    EXPECT_EQ(cache.resolve("name2"), "addrB");
    EXPECT_EQ(cache.resolve("name3"), "addrA");

    cache.update("name1", "addrC");
    EXPECT_EQ(cache.resolve("name1"), "addrC");
    EXPECT_EQ(cache.resolve("name2"), "addrB");
    EXPECT_EQ(cache.resolve("name3"), "addrA");
}

TEST(DnsCache_update, Update_Check_Earliest_Removed_One_Value) {
    DnsCache cache(1);
    cache.update("name1", "addr1");
    EXPECT_EQ(cache.resolve("name1"), "addr1");
    cache.update("name4", "addr4");
    EXPECT_TRUE(cache.resolve("name1").empty());
    EXPECT_EQ(cache.resolve("name4"), "addr4");
}

TEST(DnsCache_update, Update_Check_Earliest_Removed) {
    DnsCache cache(3);
    cache.update("name1", "addr1");
    cache.update("name2", "addr2");
    cache.update("name3", "addr3");

    cache.update("name4", "addr4");
    EXPECT_TRUE(cache.resolve("name1").empty());
    EXPECT_EQ(cache.resolve("name2"), "addr2");
    EXPECT_EQ(cache.resolve("name3"), "addr3");
    EXPECT_EQ(cache.resolve("name4"), "addr4");
}

TEST(DnsCache_update, Update_Invalid_Name) {
    DnsCache cache(3);
    cache.update("name1", "addr1");
    cache.update("name2", "addr2");
    cache.update("name3", "addr3");

    EXPECT_THROW(cache.update("", "addr4"), std::runtime_error);
}

TEST(DnsCache_update, Update_Invalid_Addr) {
    DnsCache cache(3);
    cache.update("name1", "addr1");
    cache.update("name2", "addr2");
    cache.update("name3", "addr3");

    EXPECT_THROW(cache.update("name4", ""), std::runtime_error);
}


TEST(DnsCache_update, Resolve_Update_Order) {
    DnsCache cache(3);
    cache.update("name1", "addr1");
    cache.update("name2", "addr2");
    cache.update("name3", "addr3");

    // Resolve "name1" to make it last
    EXPECT_EQ(cache.resolve("name1"), "addr1");
    // Add item to pop "name2"
    cache.update("name4", "addr4");
    EXPECT_EQ(cache.resolve("name1"), "addr1");
    EXPECT_EQ(cache.resolve("name3"), "addr3");
    EXPECT_EQ(cache.resolve("name4"), "addr4");
    EXPECT_TRUE(cache.resolve("name2").empty());

    EXPECT_NO_THROW(cache.check_integrity());
}

TEST(DnsCache_update, Resolve_Update_Order_One_Item) {
    DnsCache cache(1);
    cache.update("name1", "addr1");
    EXPECT_EQ(cache.resolve("name1"), "addr1");
    EXPECT_NO_THROW(cache.check_integrity());
}
