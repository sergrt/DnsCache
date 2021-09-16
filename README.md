# DnsCache
## Description
**DnsCache** is a test task with following description:
> You are required to implement a class for the DNS cache with the following interface:
```
class DNSCache {
public:
    explicit DNSCache(size_t max_size);
    void update(const std::string& name, const std::string& ip);
    std::string resolve(const std::string& name);
};
```
> This class stores mapping between the name and IP address. The maximum number of records available for storage is initialize in the constructor with the max_size parameter.
> 
> Function call ```update()``` either updates the existing record or adds a new one.
> 
> If the limit set by ```max_size``` is exceeded, the oldest unused records should be deleted from cache. The oldest pair (name and IP-address) that does not involved in ```update()``` or ```resolve()``` procedures longer than other
> 
> The ```resolve()``` method returns from cache the IP address for the given name parameter or a empty string if not found.
> 
> The class should support correct operation in a multithreaded application, when ```update()``` and ```resolve()``` are called from different threads at the same time.

## Implementation
Cache itself is based on ```unordered_map``` with items linked to each other to preserve order of items. Safe multithreading is granted using "Execute-around-pointer" idiom implemented in ```DnsCachePtr``` class.

## How to build
1. Get the code
    ```
    $ git clone https://github.com/sergrt/DnsCache.git
    ```
2. Enter ```test``` dir and clone ```googletest``` into ```gtest``` subdir
    ```
    $ cd DnsCache
    $ cd test
    $ git clone https://github.com/google/googletest.git gtest
    ```
3. Get one level up, make ```build``` dir and enter it
    ```
    $ cd ..
    $ mkdir build
    $ cd build
    ```
4. Generate files.
   ```
   ** Windows **
   $ cmake .. -G "Visual Studio 16 2019" .
   ** Linux **
   $ cmake .. .
   ```
5. Build files using Visual Studio (Windows) or by calling ```$ make``` (Linux)

## Questions
> What complexity does your solution provide for inserting, searching and updating records?

Am. O(1) is supposed to be for ```update()``` and ```resolve()```, linear in worst cases.

> How to prohibit creation the second instance of the class? Modify interface if required.

This should be perfectly fine to pass ```DnsCachePtr``` instance around, but as more formal implementation - this behavior can be achieved by creating a singleton by hiding constructor in ```private``` section and supply static function to get an instance, like code provided in ```DnsCachePtr.h```
```
static DnsCacheSingletonPtr& get(size_t size) {
    static DnsCacheSingletonPtr instance(size);
    return instance;
}
```
