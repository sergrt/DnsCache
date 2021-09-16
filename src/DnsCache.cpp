#include "DnsCache.h"

#include <stdexcept>

DnsCache::DnsCache(size_t max_size) : max_size_{max_size} {
    if (max_size_ == 0)
        throw std::runtime_error("DnsCache::DnsCache() - invalid cache size specified");
}

std::string DnsCache::resolve(const std::string& name) {
    if (name.empty())
        throw std::runtime_error("DnsCache::resolve() - invalid parameter passed");

    const auto i = cache_.find(name);
    if (i == cache_.cend())
        return {};

    move_item_to_end(name, i->second);
    return i->second.addr;
}

void DnsCache::update(const std::string& name, const std::string& addr) {
    if (name.empty() || addr.empty())
        throw std::runtime_error("DnsCache::update() - invalid parameter(s) passed");

    const auto emplace_res = cache_.emplace(name, AddrItem{addr});
    auto& value_affected = emplace_res.first->second;
    if (emplace_res.second) {
        update_added_item(name, value_affected);
    } else {
        value_affected.addr = addr;
        move_item_to_end(name, value_affected);
    }
}

void DnsCache::move_item_to_end(const std::string& name, AddrItem& item) {
    const auto& next = item.next_item;
    if (next.empty())
        return;

    const auto& prev = item.prev_item;
    auto n = cache_.find(next);  // If cache is contiguous this is always valid
    n->second.prev_item = prev;

    if (prev.empty()) {
        first_item_.update(item.next_item, n->second);
    } else {
        auto p = cache_.find(prev);  // If cache is contiguous this is always valid
        p->second.next_item = next;
    }

    set_item_as_last(name, item);
}

void DnsCache::set_item_as_last(const std::string& name, AddrItem& item) {
    if (last_item_.valid())
        last_item_->next_item = name;

    item.prev_item = last_item_.key;
    item.clear_next();
    last_item_.update(name, item);
}

void DnsCache::update_added_item(const std::string& name, AddrItem& item) {
    set_item_as_last(name, item);

    if (cache_.size() > max_size_)
        remove_first_item();

    if (!first_item_.valid()) {
        first_item_.update(name, item);
    }
}

void DnsCache::remove_first_item() {
    const auto old_min_key = first_item_.key;
    const auto next_min_key = first_item_.value->next_item;
    cache_.erase(old_min_key);

    auto cur = cache_.find(next_min_key);  // If cache is contiguous this is always valid
    first_item_.update(next_min_key, cur->second);
    first_item_->clear_prev();
}

void DnsCache::check_integrity() const {
    if (cache_.empty())
        return;

    std::string first_item;

    size_t count = 0;
    for (const auto& i : cache_) {
        if (i.second.prev_item.empty()) {
            first_item = i.first;
            ++count;
        }
    }

    if (first_item.empty() || count != 1)
        throw std::runtime_error("Cache integrity check failed");

    std::string cur_item = first_item;
    count = 0;
    while (!cur_item.empty()) {
        auto i = cache_.find(cur_item);
        if (i == cache_.cend())
            throw std::runtime_error("Cache integrity check failed");
        cur_item = i->second.next_item;
        ++count;
    }

    if (count != cache_.size())
        throw std::runtime_error("Cache integrity check failed");
}
