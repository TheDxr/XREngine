#pragma once

#include <vector>
#include <map>

template <typename Key, typename Val>
class DenseMap
{
public:
    DenseMap() = default;
    explicit DenseMap(int size)
    {
        data.reserve(size);
    }
    void reserve(int size)
    {
        data.reserve(size);
    }
    void insert(Key key, Val&& val)
    {
        data.emplace_back(std::forward<Val>(val));
        keyToIndex[key] = nextIndex;
        indexToKey[nextIndex] = key;
        nextIndex++;
    }
    void insert(Key key, Val& val)
    {
        int index = data.size();
        data.emplace_back(std::move(val));
        keyToIndex[key] = index;
        indexToKey[index] = key;
    }
    void remove(Key key)
    {
        int index = keyToIndex[key];
        keyToIndex.erase(key);
        indexToKey.erase(index);

        std::swap(data[index], data.back());
        data.pop_back();
        nextIndex--;
    }
    Val& operator[](Key key)
    {
        if(keyToIndex.count(key) == 0)
            insert(key, Val());
        return data[keyToIndex[key]];
    }
    Val& at(Key key)
    {
        if(keyToIndex.count(key) == 0)
            insert(key, Val());
        return data[keyToIndex[key]];
    }
    auto begin() const
    {
        return data.begin();
    }
    auto end() const
    {
        return data.end();
    }
    [[nodiscard]] size_t size() const
    {
        return data.size() + keyToIndex.size() + indexToKey.size() ;
    }
private:
    std::vector<Val> data;
    int nextIndex = 0;
    std::map<Key, int> keyToIndex;
    std::map<int, Key> indexToKey;
};