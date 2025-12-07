#include <iostream>
#include <map>
#include <vector>

std::map<int,int> countFrequency(std::vector<int> v)
{
    std::map<int,int> freq;
    
    for(auto x: v) 
    {
        
        freq[x]++;
    }
    return freq;
}

std::map<char, std::vector<std::string>> groupByFirstChar(const std::vector<std::string>& stVec)
{
    std::map<char, std::vector<std::string>> group;
    
    for(std::string elem : stVec)
    {
        if(!elem.empty())
        {
            group[elem[0]].push_back(elem);
        }    
    }
    return group;
}

std::map<std::string, int> mergeMaps(const std::map<std::string, int>& m1, const std::map<std::string, int>& m2)
{
    std::map<std::string, int> result = m1;  

    for (const auto& [key, value] : m2) 
    {
        result[key] += value;  
    }
    return result;
}

int firstUniqueChar(const std::string& s) 
{
    std::map<char, int> freq;
    
    for (char c : s) 
    {
        freq[c]++;
    }

    for (int i = 0; i < (int)s.size(); i++) 
    {
        if (freq[s[i]] == 1) 
        {
            return i;
        }
    }
    return -1;
}

std::vector<std::vector<std::string>> groupAnagrams(const std::vector<std::string>& strs) 
{
    std::map<std::string, std::vector<std::string>> groups;

    for (const auto& s : strs) 
    {
        std::string key = s;
        std::sort(key.begin(), key.end()); 
        groups[key].push_back(s);
    }

    std::vector<std::vector<std::string>> result;
    for (auto& pair : groups) 
    {
        result.push_back(pair.second);
    }

    return result;
}

bool cmpPairs(const std::pair<int,int>& a, const std::pair<int,int>& b)
{
    if (a.second != b.second) return a.second > b.second;
    return a.first < b.first;
}

std::vector<int> topKFrequent(const std::vector<int>& nums, int k)
{
    std::map<int,int> freq;
    for (int x : nums) 
    {
        ++freq[x];
    }

    std::vector<std::pair<int,int>> arr;
    for (auto &p : freq) 
    {
        arr.push_back(p);
    }

    std::sort(arr.begin(), arr.end(), cmpPairs);

    std::vector<int> res;
    for (size_t i = 0; i < arr.size() && res.size() < (size_t)k; ++i)
    {
        res.push_back(arr[i].first);
    }
    return res;
}

bool isIsomorphic(const std::string& s, const std::string& t)
{
    if (s.size() != t.size()) return false;

    std::map<char,char> m1, m2;

    for (size_t i = 0; i < s.size(); ++i)
    {
        char a = s[i], b = t[i];

        if (m1.count(a))
        {
            if (m1[a] != b) return false;
        }
        else m1[a] = b;

        if (m2.count(b))
        {
            if (m2[b] != a) return false;
        }
        else m2[b] = a;
    }
    return true;
}

std::vector<int> arrayRankTransform(const std::vector<int>& arr)
{
    std::map<int,int> rank;
    std::vector<int> uniq = arr;

    std::sort(uniq.begin(), uniq.end());
    uniq.erase(std::unique(uniq.begin(), uniq.end()), uniq.end());

    for (size_t i = 0; i < uniq.size(); ++i)
        rank[uniq[i]] = (int)i + 1;

    std::vector<int> res;
    res.reserve(arr.size());

    for (int x : arr) res.push_back(rank[x]);

    return res;
}

int rangeSumMap(const std::map<int,int>& m, int left, int right)
{
    auto it = m.lower_bound(left);
    int sum = 0;

    while (it != m.end() && it->first <= right)
    {
        sum += it->second;
        ++it;
    }

    return sum;
}

template<typename K, typename V>
class BidirectionalMap
{
public:

    bool insert(const K& key, const V& value)
    {
        if (key_to_val.count(key) || val_to_key.count(value)) return false;

        key_to_val[key] = value;
        val_to_key[value] = key;
        return true;
    }

    V getByKey(const K& key) const
    {
        auto it = key_to_val.find(key);
        if (it == key_to_val.end()) throw std::out_of_range("key not found");
        return it->second;
    }

    K getByValue(const V& value) const
    {
        auto it = val_to_key.find(value);
        if (it == val_to_key.end()) throw std::out_of_range("value not found");
        return it->second;
    }

    bool removeByKey(const K& key)
    {
        auto it = key_to_val.find(key);
        if (it == key_to_val.end()) return false;

        V v = it->second;
        key_to_val.erase(it);
        val_to_key.erase(v);
        return true;
    }

private:
    std::map<K,V> key_to_val;
    std::map<V,K> val_to_key;
};

int removeInfrequent(std::map<std::string,int>& freq, int threshold)
{
    int removed = 0;

    for (auto it = freq.begin(); it != freq.end(); )
    {
        if (it->second < threshold)
        {
            it = freq.erase(it);
            ++removed;
        }
        else ++it;
    }

    return removed;
}

int main()
{
    return 0;
}