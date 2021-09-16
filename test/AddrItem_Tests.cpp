// AddrItem class tests

#include "gtest/gtest.h"

#include "AddrItem.h"

constexpr auto addr = "addr";
constexpr auto prev = "prev";
constexpr auto next = "next";

TEST(AddrItem, Construct_Complete) {
    const auto addr_item = AddrItem(addr, prev, next);

    EXPECT_EQ(addr_item.addr, addr);
    EXPECT_EQ(addr_item.prev_item, prev);
    EXPECT_EQ(addr_item.next_item, next);
}

TEST(AddrItem, Construct_Short) {
    const auto addr_item = AddrItem(addr);

    EXPECT_EQ(addr_item.addr, addr);
    EXPECT_TRUE(addr_item.prev_item.empty());
    EXPECT_TRUE(addr_item.next_item.empty());
}

TEST(AddrItem, Construct_Complete_Invalid) {
    EXPECT_THROW(AddrItem("", prev, next), std::runtime_error);
    EXPECT_THROW(AddrItem(addr, "", next), std::runtime_error);
    EXPECT_THROW(AddrItem(addr, prev, ""), std::runtime_error);
    EXPECT_THROW(AddrItem("", "", ""), std::runtime_error);
}

TEST(AddrItem, Construct_Short_Invalid) {
    EXPECT_THROW(AddrItem(""), std::runtime_error);
}

TEST(AddrItem, ClearPrev) {
    auto addr_item = AddrItem(addr, prev, next);

    EXPECT_EQ(addr_item.addr, addr);
    EXPECT_EQ(addr_item.prev_item, prev);
    EXPECT_EQ(addr_item.next_item, next);

    addr_item.clear_prev();
    EXPECT_EQ(addr_item.addr, addr);
    EXPECT_TRUE(addr_item.prev_item.empty());
    EXPECT_EQ(addr_item.next_item, next);
}

TEST(AddrItem, ClearNext) {
    auto addr_item = AddrItem(addr, prev, next);

    EXPECT_EQ(addr_item.addr, addr);
    EXPECT_EQ(addr_item.prev_item, prev);
    EXPECT_EQ(addr_item.next_item, next);

    addr_item.clear_next();
    EXPECT_EQ(addr_item.addr, addr);
    EXPECT_EQ(addr_item.prev_item, prev);
    EXPECT_TRUE(addr_item.next_item.empty());
}
