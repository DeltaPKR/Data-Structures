#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

std::vector<int> removeDublicates(const std::vector<int>& ref)
{
    std::set<int> unique(ref.begin(), ref.end());
    
    return std::vector<int>(unique.begin(), unique.end());
}

std::vector<int> findIntersection(const std::vector<int>& first, const std::vector<int>& second)
{
    std::set<int> A(first.begin(), first.end());
    std::set<int> B(second.begin(), second.end());
    
    std::vector<int> result;
    
    for(auto elem : A)
    {
        if(B.find(elem) != B.end()) result.push_back(elem);
    }
    
    return result;
}

bool isSubset(const std::vector<int>& first, const std::vector<int>& second)
{
    std::set<int> st1(first.begin(), first.end());
    std::set<int> st2(second.begin(), second.end());
    
    for(auto elem : st1)
    {
        if(st2.find(elem) == st2.end()) return false;
    }
    
    return true;
}

std::vector<int> findMissingNumbers(const std::vector<int>& ref, int N)
{
    std::set<int> st(ref.begin(), ref.end());
    std::vector<int> result;
    
    for(int i = N; i > 0; i--)
    {
        if(st.find(i) == st.end()) result.push_back(i);
    }
    std::reverse(result.begin(), result.end());
    return result;
}

int findClosest(const std::set<int>& ref, int target)
{
    if(ref.empty()) return -1;
    
    auto it = ref.lower_bound(target);
    
    if(it == ref.begin()) return *it;
    else if(it == ref.end())
    {
        it--;
        return *it;
    }
    
    int curr = *it;
    --it;
    int prev = *it;
    
    if(abs(curr - prev) >= abs(prev - curr)) return prev;
    return curr;
}

int rangeCount(const std::set<int>& ref, int low, int high)
{
    if(low > high || ref.empty()) return 0;
    
    int count = 0;
    
    for(auto it = ref.lower_bound(low); it != ref.upper_bound(high); ++it)
    {
        count++;
    }
    return count;
}

std::vector<int> symmetricDifference(const std::vector<int>& first, const std::vector<int>& second)
{
    std::set<int> A(first.begin(), first.end());
    std::set<int> B(second.begin(), second.end());
    
    std::vector<int> result;
    
    for(auto elem : A)
    {
        if(B.count(elem) == 0)
        {
            result.push_back(elem);
        }
    }
    for(auto elem : B)
    {
        if(A.count(elem) == 0)
        {
            result.push_back(elem);
        }
    }
    
    return result;
}

int firstRepeating(const std::vector<int>& nums) 
{
    std::set<int> seen;

    for (auto elem : nums) 
    {
        if (seen.count(elem)) 
        {
            return elem;
        }
        seen.insert(elem);
    }
    return -1;
}

int removeRange(std::set<int>& st, int low, int high)
{
    if(low > high || st.empty()) return 0;
    
    int count = 0;
    
    for(auto it = st.lower_bound(low); it != st.upper_bound(high); ++it)
    {
        count++;
    }
    
    st.erase(st.lower_bound(low), st.upper_bound(high));
    return count;
}

int main()
{
    std::vector<int> nums = {2, 2, 5, 2, 3, 4, 1};
    std::vector<int> noDuplicates = removeDublicates(nums);
    
    for(auto elem : noDuplicates)
    {
        std::cout << elem << ' ';
    }
    std::cout << std::endl;
    
    std::vector<int> v1 = {1, 2, 3, 4, 5};
    std::vector<int> v2 = {2, 4};
    
    std::vector<int> v3 = findIntersection(v1, v2);
    
    for(auto elem : v3)
    {
        std::cout << elem << ' ';
    }
    std::cout << std::endl;
    
    std::vector<int> first = {1, 2, 3};
    std::vector<int> second = {1, 2, 3, 4, 5};
    
    std::cout << (isSubset(first, second) ? "yes" : "no") << std::endl;
    
    std::vector<int> num = {1, 3, 5, 6};
    std::vector<int> result = findMissingNumbers(num, 6);
    
    for(auto elem : result)
    {
        std::cout << elem << ' ';
    }
    std::cout << std::endl;
    
    std::set<int> s = {1, 5, 10, 15, 20};
    std::cout << findClosest(s, 12) << std::endl;
    
    std::vector<int> arr1 = {1, 2, 3, 4};
    std::vector<int> arr2 = {3, 4, 5, 6};
    auto res = symmetricDifference(arr1, arr2);
    
    for(auto elem : res)
    {
        std::cout << elem << ' ';
    }
    std::cout << std::endl;
    
    std::vector<int> numbers = {1, 2, 3, 4, 2, 5, 6, 3};
    std::cout << firstRepeating(numbers) << std::endl;
    
    std::set st = {1, 3, 5, 7, 9, 11, 13, 15};
    int removed = removeRange(st, 5, 11);
    
    std::cout << removed << std::endl;
    for(auto elem : st)
    {
        std::cout << elem << ' ';
    }
    std::cout << std::endl;
    
    return 0;
}