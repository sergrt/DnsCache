#include "AddrItem.h"

#include <stdexcept>

AddrItem::AddrItem(const std::string& ip, const std::string& prev, const std::string& next)
    : addr(ip), prev_item(prev), next_item(next) {

    if (addr.empty() || prev_item.empty() || next_item.empty())
        throw std::runtime_error("AddrItem() - invalid parameters");
}

AddrItem::AddrItem(const std::string& ip)
    : addr(ip) {
    if (addr.empty())
        throw std::runtime_error("AddrItem() - invalid parameters");
}

void AddrItem::clear_prev() {
    prev_item = {};
}

void AddrItem::clear_next() {
    next_item = {};
}
