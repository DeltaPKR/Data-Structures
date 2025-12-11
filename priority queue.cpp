#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

std::vector<int> heapSortAscending(const std::vector<int>& nums)
{
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
    for (int x : nums)
    {
        pq.push(x);
    }
    std::vector<int> res;
    while (!pq.empty())
    {
        res.push_back(pq.top());
        pq.pop();
    }
    return res;
}

std::vector<int> kLargest(const std::vector<int>& v, int k)
{
    std::priority_queue<int> pq;
    for (int x : v)
    {
        pq.push(x);
    }
    std::vector<int> res;
    for (int i = 0; i < k && !pq.empty(); ++i)
    {
        res.push_back(pq.top());
        pq.pop();
    }
    return res;
}

int kthSmallest_maxHeap(const std::vector<int>& nums, int k)
{
    std::priority_queue<int> pq;
    for (int x : nums)
    {
        pq.push(x);
        if ((int)pq.size() > k)
        {
            pq.pop();
        }
    }
    return pq.top();
}

int kthSmallest_minHeap(const std::vector<int>& nums, int k)
{
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
    for (int x : nums)
    {
        pq.push(x);
    }
    for (int i = 1; i < k; ++i)
    {
        pq.pop();
    }
    return pq.top();
}

int kthLargest(const std::vector<int>& a, int k)
{
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
    for (int x : a)
    {
        pq.push(x);
        if ((int)pq.size() > k)
        {
            pq.pop();
        }
    }
    return pq.top();
}

bool isHeap(const std::vector<int>& a)
{
    int n = (int)a.size();
    for (int i = 0; i < n; ++i)
    {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (l < n && a[i] < a[l]) return false;
        if (r < n && a[i] < a[r]) return false;
    }
    return true;
}

std::vector<std::pair<int,int>> mergeIntervals(const std::vector<std::pair<int,int>>& intervals)
{
    if (intervals.empty()) return { };
    struct Cmp
    {
        bool operator()(const std::pair<int,int>& a, const std::pair<int,int>& b) const
        {
            if (a.first == b.first) return a.second > b.second;
            return a.first > b.first;
        }
    };
    std::priority_queue<
        std::pair<int,int>,
        std::vector<std::pair<int,int>>,
        Cmp
    > pq;

    for (auto& p : intervals)
    {
        pq.push(p);
    }

    std::vector<std::pair<int,int>> sorted;
    while (!pq.empty())
    {
        sorted.push_back(pq.top());
        pq.pop();
    }

    std::vector<std::pair<int,int>> res;
    res.push_back(sorted[0]);
    for (size_t i = 1; i < sorted.size(); ++i)
    {
        auto& last = res.back();
        if (sorted[i].first <= last.second)
        {
            last.second = std::max(last.second, sorted[i].second);
        }
        else
        {
            res.push_back(sorted[i]);
        }
    }
    return res;
}

struct Task
{
    int priority;
    std::string name;
};

struct TaskCmp
{
    bool operator()(const Task& a, const Task& b) const
    {
        if (a.priority == b.priority) return a.name > b.name;
        return a.priority < b.priority;
    }
};

struct TaskScheduler
{
    std::priority_queue<Task, std::vector<Task>, TaskCmp> pq;

    void add(const Task& t)
    {
        pq.push(t);
    }

    Task next()
    {
        Task t = pq.top();
        pq.pop();
        return t;
    }

    bool empty() const
    {
        return pq.empty();
    }
};

struct MedianFinder
{
    std::priority_queue<int> left;
    std::priority_queue<int, std::vector<int>, std::greater<int>> right;

    void addNum(int num)
    {
        if (left.empty() || num <= left.top())
        {
            left.push(num);
        }
        else
        {
            right.push(num);
        }
        if ((int)left.size() > (int)right.size() + 1)
        {
            right.push(left.top());
            left.pop();
        }
        else if ((int)right.size() > (int)left.size())
        {
            left.push(right.top());
            right.pop();
        }
    }

    double findMedian()
    {
        if (left.size() == right.size())
        {
            return (left.top() + right.top()) / 2.0;
        }
        return left.top();
    }
};

struct Point
{
    int x;
    int y;
};

std::vector<Point> kClosest(const std::vector<Point>& pts, int k)
{
    auto dist2 = [&](const Point& p)
    {
        return 1LL * p.x * p.x + 1LL * p.y * p.y;
    };

    auto cmp = [&](const Point& a, const Point& b)
    {
        return dist2(a) < dist2(b);
    };

    std::priority_queue<Point, std::vector<Point>, decltype(cmp)> pq(cmp);

    for (auto& p : pts)
    {
        pq.push(p);
        if ((int)pq.size() > k)
        {
            pq.pop();
        }
    }

    std::vector<Point> res;
    while (!pq.empty())
    {
        res.push_back(pq.top());
        pq.pop();
    }
    std::reverse(res.begin(), res.end());
    return res;
}

struct CPUJob
{
    int time;
    int priority;
    std::string name;
};

struct CPUJobCmp
{
    bool operator()(const CPUJob& a, const CPUJob& b) const
    {
        if (a.priority == b.priority) return a.time > b.time;
        return a.priority < b.priority;
    }
};

struct CPU
{
    std::priority_queue<CPUJob, std::vector<CPUJob>, CPUJobCmp> pq;

    void add(const CPUJob& j)
    {
        pq.push(j);
    }

    CPUJob run()
    {
        CPUJob j = pq.top();
        pq.pop();
        return j;
    }

    bool empty() const
    {
        return pq.empty();
    }
};

bool isValidPopSequence(const std::vector<int>& removed)
{
    for (size_t i = 1; i < removed.size(); ++i)
    {
        if (removed[i - 1] <= removed[i]) return false;
    }
    return true;
}

int main()
{
    std::vector<int> nums1 = { 4, 2, 8, 1, 9, 3 };
    auto sorted1 = heapSortAscending(nums1);
    for (int x : sorted1) std::cout << x << " ";
    std::cout << std::endl;

    std::vector<int> v2 = { 10, 30, 50, 20, 40 };
    auto kl = kLargest(v2, 3);
    for (int x : kl) std::cout << x << " ";
    std::cout << std::endl;

    std::vector<int> nums3 = { 7, 10, 4, 3, 20, 15, -1, 8 };
    std::cout << kthSmallest_maxHeap(nums3, 3) << std::endl;
    std::cout << kthSmallest_minHeap(nums3, 3) << std::endl;

    std::vector<int> a4 = { 3, 2, 1, 5, 6, 4 };
    std::cout << kthLargest(a4, 2) << std::endl;

    std::vector<int> a5 = { 50, 30, 40, 10, 20 };
    std::cout << (isHeap(a5) ? "true" : "false") << std::endl;

    std::vector<std::pair<int,int>> iv = { {1,3}, {2,6}, {8,10}, {9,12} };
    auto merged = mergeIntervals(iv);
    for (auto& p : merged) std::cout << "{" << p.first << "," << p.second << "} ";
    std::cout << std::endl;

    TaskScheduler ts;
    ts.add(Task{5, "compile"});
    ts.add(Task{10, "fix bug"});
    ts.add(Task{7, "build"});
    auto t = ts.next();
    std::cout << t.name << " " << t.priority << std::endl;

    MedianFinder mf;
    mf.addNum(1);
    mf.addNum(2);
    std::cout << mf.findMedian() << std::endl;
    mf.addNum(3);
    std::cout << mf.findMedian() << std::endl;

    std::vector<Point> pts = { {1,3}, {-2,2}, {5,8} };
    auto clos = kClosest(pts, 2);
    for (auto& p : clos) std::cout << "{" << p.x << "," << p.y << "} ";
    std::cout << std::endl;

    CPU cpu;
    cpu.add(CPUJob{3, 10, "taskA"});
    cpu.add(CPUJob{1, 5, "taskB"});
    cpu.add(CPUJob{2, 7, "taskC"});
    auto next = cpu.run();
    std::cout << next.priority << " " << next.time << " " << next.name << std::endl;

    std::vector<int> removed = { 100, 50, 40, 10 };
    std::cout << (isValidPopSequence(removed) ? "true" : "false") << std::endl;

    return 0;
}
