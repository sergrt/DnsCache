#pragma once

#include "DnsCache.h"

#include <memory>
#include <mutex>

class DnsCachePtr {
    class obj_locked {
        DnsCache* const dns_cache_;
        std::unique_lock<std::recursive_mutex> lock_;

    public:
        obj_locked(DnsCache* const dns_cache, std::recursive_mutex& lock);
        DnsCache* operator->();
    };

    const std::shared_ptr<DnsCache> dns_cache_;
    std::shared_ptr<std::recursive_mutex> lock_ = std::make_shared<std::recursive_mutex>();

public:
    explicit DnsCachePtr(size_t size);

    obj_locked operator->();
};

/* Declaration of singleton

class DnsCacheSingletonPtr {
    class obj_locked {
        DnsCache* const dns_cache_;
        std::unique_lock<std::recursive_mutex> lock_;

    public:
        obj_locked(DnsCache* const dns_cache, std::recursive_mutex& lock);
        DnsCache* operator->();
    };

    const std::shared_ptr<DnsCache> dns_cache_;
    std::shared_ptr<std::recursive_mutex> lock_ = std::make_shared<std::recursive_mutex>();

    explicit DnsCacheSingletonPtr(size_t size);

public:
    static DnsCacheSingletonPtr& get(size_t size) {
        static DnsCacheSingletonPtr instance(size);
        return instance;
    }
    DnsCacheSingletonPtr(const DnsCacheSingletonPtr&) = delete;
    void operator=(const DnsCacheSingletonPtr&) = delete;

    obj_locked operator->();
};
*/
