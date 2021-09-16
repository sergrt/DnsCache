#pragma once

#include "AddrItem.h"

#include <string>
#include <unordered_map>

class DnsCache {
public:
    explicit DnsCache(size_t max_size);

    std::string resolve(const std::string& name);
    void update(const std::string& name, const std::string& addr);

    // Check cache linkage for integrity. Useful for testing purposes
    void check_integrity() const;

 private:
    void move_item_to_end(const std::string& name, AddrItem& item);
    void update_added_item(const std::string& name, AddrItem& item);
    void set_item_as_last(const std::string& name, AddrItem& item);
    void remove_first_item();

    // Internal refs rely on the assumption that no reference invalidation of cache_
    // takes place in any function of the DnsCache class.
    struct InternalRef {
        std::string key;
        AddrItem* value = nullptr;

        AddrItem* operator->() {
            return value;
        }
        [[nodiscard]] bool valid() const {
            return value != nullptr;
        }
        void update(const std::string& k, AddrItem& v) {
            key = k;
            value = &v;
        }
    };

    InternalRef first_item_;
    InternalRef last_item_;

    size_t max_size_ = 0;
    std::unordered_map<std::string, AddrItem> cache_;
};
