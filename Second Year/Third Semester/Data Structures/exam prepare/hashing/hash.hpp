#ifndef __Hash_HPP
#define __Hash_HPP

#include <iostream>

class HashingFunction{
public:
    virtual ~HashingFunction() = default;
    virtual std::size_t calculateHashCode(int key) = 0;
};

class ModAndMultHashingFunction : public HashingFunction{
private: 
    std::size_t mod;
    std::size_t multiplier;
public:
    ModAndMultHashingFunction(std::size_t mod, std::size_t multiplier) : mod(mod), multiplier(multiplier) {}
    std::size_t calculateHashCode(int key) override{
        return (key % mod) * multiplier;
    }
};

template<typename ValType>
class Hash{
protected:
    HashingFunction *hashFunc;
public:
    Hash(HashingFunction *hashFunc=nullptr) : hashFunc(hashFunc) {}

    virtual ~Hash() = default;
    virtual void insert(int key, ValType const &val) = 0;
    virtual ValType const &find(int key) const = 0;
    virtual bool remove(int key) = 0;
};

#endif