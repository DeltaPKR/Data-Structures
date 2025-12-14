#include <vector>
#include <list>
#include <utility>
#include <functional>
#include <string>
#include <iostream>

template <typename K, typename V>
class HashTable
{
private:
    using NodeType = std::pair<K, V>;
    std::vector<std::list<NodeType>> buckets;

    size_t numElements;
    double maxLoadFactor;

    size_t getBucketIndex(const K& key) const
    {
        std::hash<K> hasher;
        return hasher(key) % buckets.size();
    }

    double getLoadFactor() const
    {
        return static_cast<double>(numElements) / buckets.size();
    }

    void rehash()
    {
        std::vector<std::list<NodeType>> oldBuckets = buckets;
        buckets.clear();
        buckets.resize(oldBuckets.size() * 2);

        numElements = 0;

        for (auto &bucket : oldBuckets)
        {
            for (auto &node : bucket)
            {
                insert(node.first, node.second);
            }
        }
    }

public:
    HashTable(size_t initialCapacity = 8) : numElements(0), maxLoadFactor(0.75)
    {
        if (initialCapacity < 1)
        {
            initialCapacity = 8;
        }
        buckets.resize(initialCapacity);
    }

    void insert(const K& key, const V& value)
    {
        size_t idx = getBucketIndex(key);

        for (auto &x : buckets[idx])
        {
            if (x.first == key)
            {
                x.second = value;
                return;
            }
        }

        buckets[idx].push_back({ key, value });
        ++numElements;

        if (getLoadFactor() > maxLoadFactor)
        {
            rehash();
        }
    }

    V* find(const K& key)
    {
        size_t idx = getBucketIndex(key);

        for (auto &x : buckets[idx])
        {
            if (x.first == key)
            {
                return &x.second;
            }
        }
        return nullptr;
    }

    bool remove(const K& key)
    {
        size_t idx = getBucketIndex(key);

        for (auto it = buckets[idx].begin(); it != buckets[idx].end(); ++it)
        {
            if (it->first == key)
            {
                buckets[idx].erase(it);
                --numElements;
                return true;
            }
        }

        return false;
    }

    size_t size() const
    {
        return numElements;
    }

    bool empty() const
    {
        return numElements == 0;
    }

    void clear()
    {
        for (auto &bucket : buckets)
        {
            bucket.clear();
        }
        numElements = 0;
    }

    size_t getMaxBucketSize() const
    {
        size_t maxSize = 0;

        for (const auto &bucket : buckets)
        {
            if (bucket.size() > maxSize)
            {
                maxSize = bucket.size();
            }
        }
        return maxSize;
    }
};

int main()
{
    return 0;
}
