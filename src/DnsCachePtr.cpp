#include "DnsCachePtr.h"

DnsCachePtr::obj_locked::obj_locked(DnsCache* const dns_cache, std::recursive_mutex& lock)
    : dns_cache_(dns_cache), lock_(lock) {}

DnsCache* DnsCachePtr::obj_locked::operator->() {
    return dns_cache_;
}

DnsCachePtr::DnsCachePtr(size_t size) : dns_cache_(new DnsCache(size)) {}

DnsCachePtr::obj_locked DnsCachePtr::operator->() {
    return obj_locked(dns_cache_.get(), *lock_);
}


/* Implementation of singleton

DnsCacheSingletonPtr::obj_locked::obj_locked(DnsCache* const dns_cache, std::recursive_mutex& lock)
    : dns_cache_(dns_cache), lock_(lock) {}

DnsCache* DnsCacheSingletonPtr::obj_locked::operator->() {
    return dns_cache_;
}

DnsCacheSingletonPtr::DnsCacheSingletonPtr(size_t size) : dns_cache_(new DnsCache(size)) {}

DnsCacheSingletonPtr::obj_locked DnsCacheSingletonPtr::operator->() {
    return obj_locked(dns_cache_.get(), *lock_);
}
*/
