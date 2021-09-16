// Integrity tests

#include "gtest/gtest.h"

#include "DnsCachePtr.h"

#include <thread>

TEST(Integrity, Update) {
    for (int sz = 1; sz < 10; ++sz) {
        DnsCachePtr cache_ptr(sz);
        for (int j = 0; j < 2 * sz; ++j) {
            const std::string name = "name" + std::to_string(j);
            const std::string addr = "addr" + std::to_string(j);
            cache_ptr->update(name, addr);
            EXPECT_NO_THROW(cache_ptr->check_integrity());
        }
    }
}

TEST(Integrity, Update_Multithread) {
    std::cerr << "Integrity (multithreaded) - might take some time...\n";
    // This test might take some time (depend on hardware)
    auto threads_count = std::thread::hardware_concurrency() - 1;
    if (threads_count <= 0)
        threads_count = 8;

    for (int sz = 100'000; sz < 100'003; ++sz) {
        std::vector<std::thread> vec_thread(threads_count);
        DnsCachePtr cache_ptr(sz);
        for (auto& t : vec_thread) {
            t = std::move(std::thread(
                [sz](DnsCachePtr cache) {
                    for (int i = 0; i < sz + 1; ++i) {
                        const auto c = rand() % ('z' - 'a' + 1) + 'a';
                        const auto name = "abcd_" + std::string(1, static_cast<char>(c));
                        const auto addr = name; // Used to check anomaly

                        const auto op = rand() % 2;
                        if (op == 0) {
                            cache->update(name, name);
                        } else {
                            const auto cached_addr = cache->resolve(name);
                            if (cached_addr.empty()) {
                                cache->update(name, addr);
                            } else if (name != cached_addr) {
                                throw std::runtime_error("something wrong");
                            }
                        }
                        EXPECT_NO_THROW(cache->check_integrity());
                    }
                }, cache_ptr));
        }
            
        for (auto& i : vec_thread)
            i.join();
    }
}