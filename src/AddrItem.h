#pragma once

#include <string>

struct AddrItem {
    AddrItem(const std::string& ip, const std::string& prev, const std::string& next);
    AddrItem(const std::string& ip);

    // Just for convenience, to avoid raw strings manipulations on calling side
    void clear_prev();
    void clear_next();

    std::string addr;

    // Names, keys of cache of sibling items. It would be better to distinct them of plain strings
    // to avoid confusion here.
    std::string prev_item;
    std::string next_item;
};
