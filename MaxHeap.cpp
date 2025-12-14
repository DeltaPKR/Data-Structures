#include <vector>
#include <stdexcept>
#include <iostream>

template <typename T>
class MaxHeap
{
private:
    std::vector<T> heap;

    size_t parent(size_t i) const
    {
        return (i - 1) / 2;
    }

    size_t leftChild(size_t i) const
    {
        return 2 * i + 1;
    }

    size_t rightChild(size_t i) const
    {
        return 2 * i + 2;
    }

    void siftUp(size_t i)
    {
        while (i > 0 && heap[parent(i)] < heap[i])
        {
            std::swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    void siftDown(size_t i)
    {
        size_t n = heap.size();

        while (true)
        {
            size_t l = leftChild(i);
            size_t r = rightChild(i);
            size_t largest = i;

            if (l < n && heap[largest] < heap[l]) largest = l;

            if (r < n && heap[largest] < heap[r]) largest = r;

            if (largest == i) break;

            std::swap(heap[i], heap[largest]);
            i = largest;
        }
    }

public:
    MaxHeap() {}

    MaxHeap(const std::vector<T>& data)
    {
        heap = data;
        if (heap.empty()) return;

        for (int i = static_cast<int>(heap.size() / 2) - 1; i >= 0; --i)
            siftDown(i);
    }

    void push(const T& value)
    {
        heap.push_back(value);
        siftUp(heap.size() - 1);
    }

    void pop()
    {
        if (heap.empty()) throw std::out_of_range("Heap is empty");

        heap[0] = heap.back();
        heap.pop_back();

        if (!heap.empty()) siftDown(0);
    }

    const T& top() const
    {
        if (heap.empty()) throw std::out_of_range("Heap is empty");

        return heap[0];
    }

    size_t size() const
    {
        return heap.size();
    }

    bool empty() const
    {
        return heap.empty();
    }

    void clear()
    {
        heap.clear();
    }

    static bool isHeap(const std::vector<T>& data)
    {
        size_t n = data.size();

        for (size_t i = 0; i < n; ++i)
        {
            size_t l = 2 * i + 1;
            size_t r = 2 * i + 2;

            if (l < n && data[i] < data[l]) return false;

            if (r < n && data[i] < data[r]) return false;
        }
        return true;
    }
};

int main()
{
    return 0;
}