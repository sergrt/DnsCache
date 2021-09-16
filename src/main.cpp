#include "DnsCachePtr.h"

#include <iostream>

constexpr size_t cache_size = 3;

int main() {
    std::cout << "Some cache manipulations:\n";
    std::cout << "    create cache of size " << cache_size << "\n";
    DnsCachePtr cache_ptr(cache_size);
    std::cout << "    try to resolve \"abc.def\", result = \"" << cache_ptr->resolve("abc.def") << "\"\n";
    std::cout << "    add \"abc.def\" = \"0.1.2.3\"\n";
    cache_ptr->update("abc.def", "0.1.2.3");
    std::cout << "    try to resolve \"abc.def\", result = \"" << cache_ptr->resolve("abc.def") << "\"\n";
    std::cout << "    add 3 more items\n";
    std::cout << "        add \"aaa.bbb\" = \"1.1.1.1\"\n";
    cache_ptr->update("aaa.bbb", "1.1.1.1");
    std::cout << "        add \"ccc.ddd\" = \"2.2.2.2\"\n";
    cache_ptr->update("ccc.ddd", "2.2.2.2");
    std::cout << "        add \"eee.fff\" = \"3.3.3.3\"\n";
    cache_ptr->update("eee.fff", "3.3.3.3");
    std::cout << "    try to resolve \"abc.def\", result = \"" << cache_ptr->resolve("abc.def") << "\"\n";
    std::cout << "    try to resolve \"aaa.bbb\", result = \"" << cache_ptr->resolve("aaa.bbb") << "\"\n";
    std::cout << "    try to resolve \"ccc.ddd\", result = \"" << cache_ptr->resolve("ccc.ddd") << "\"\n";
    std::cout << "    try to resolve \"eee.fff\", result = \"" << cache_ptr->resolve("eee.fff") << "\"\n";
    std::cout << "    ...check integrity...";
    cache_ptr->check_integrity();
    std::cout << "OK\n";

    std::cout << "    update \"eee.fff\" with value \"4.4.4.4\"\n";
    cache_ptr->update("eee.fff", "4.4.4.4");
    std::cout << "    try to resolve \"eee.fff\", result = \"" << cache_ptr->resolve("eee.fff") << "\"\n";

    std::cout << "    ...check integrity...";
    cache_ptr->check_integrity();
    std::cout << "OK\n";

    std::cout << "    resolve \"ccc.ddd\" to make it last, result = \"" << cache_ptr->resolve("ccc.ddd") << "\"\n";
    std::cout << "    add 2 more items to pop some data\n";
    std::cout << "        add \"ggg.hhh\" = \"5.5.5.5\"\n";
    cache_ptr->update("ggg.hhh", "5.5.5.5");
    std::cout << "        add \"iii.jjj\" = \"6.6.6.6\"\n";
    cache_ptr->update("iii.jjj", "6.6.6.6");

    std::cout << "    ensure \"ccc.ddd\" is still in cache, result = \"" << cache_ptr->resolve("ccc.ddd") << "\"\n";

    std::cout << "    try to resolve \"abc.def\", result = \"" << cache_ptr->resolve("abc.def") << "\"\n";
    std::cout << "    try to resolve \"aaa.bbb\", result = \"" << cache_ptr->resolve("aaa.bbb") << "\"\n";
    std::cout << "    try to resolve \"ccc.ddd\", result = \"" << cache_ptr->resolve("ccc.ddd") << "\"\n";
    std::cout << "    try to resolve \"eee.fff\", result = \"" << cache_ptr->resolve("eee.fff") << "\"\n";
    std::cout << "    try to resolve \"ggg.hhh\", result = \"" << cache_ptr->resolve("ggg.hhh") << "\"\n";
    std::cout << "    try to resolve \"iii.jjj\", result = \"" << cache_ptr->resolve("iii.jjj") << "\"\n";

    std::cout << "    ...check integrity...";
    cache_ptr->check_integrity();
    std::cout << "OK\n";

    std::cout << "Finished\n";
    return 0;
}
