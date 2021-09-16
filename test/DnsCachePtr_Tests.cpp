// DnsCachePtr class tests

#include "gtest/gtest.h"

#include "DnsCachePtr.h"

TEST(DnsCachePtr, Construct_valid) {
    DnsCachePtr cache_ptr(3);
    cache_ptr->update("name1", "addr1");
    cache_ptr->update("name2", "addr2");
    cache_ptr->update("name3", "addr3");
    cache_ptr->update("name4", "addr4");

    EXPECT_TRUE(cache_ptr->resolve("name1").empty());
    EXPECT_EQ(cache_ptr->resolve("name2"), "addr2");
    EXPECT_EQ(cache_ptr->resolve("name3"), "addr3");
    EXPECT_EQ(cache_ptr->resolve("name4"), "addr4");
}

TEST(DnsCachePtr, Construct_invalid) {
    EXPECT_THROW(DnsCachePtr(0), std::runtime_error);
}

TEST(DnsCachePtr, Check_Multilock) {
    DnsCachePtr cache_ptr(1);

    // This is UB, but some implementations may throw std::system_error, so check it here
    EXPECT_NO_THROW(std::cout << cache_ptr->resolve("name1") << cache_ptr->resolve("name2"));
}