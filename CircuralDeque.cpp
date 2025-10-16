#include <iostream>

using namespace std;

template <typename T>
class CircuralDeque
{
private:
    T* buffer = nullptr;
    int size;
    int capacity;
    int front;
    int rear;
    
    void resize()
    {
        if (capacity == size)
        {
            int newCap = (capacity == 0 ? 4 : capacity * 2);
            T* buff = new T[newCap];
            
            for (int i = 0; i < size; ++i)
            {
                buff[i] = buffer[(front + i) % capacity];
            }
            
            delete[] buffer;
            buffer = buff;
            capacity = newCap;
            front = 0;
            rear = (size == 0 ? -1 : size - 1);
        }
    }
    
public:
    CircuralDeque(int initialSize = 0)
    {
        capacity = initialSize > 0 ? initialSize : 1;
        buffer = new T[capacity];
        size = 0;
        front = -1;
        rear = -1;
    }
    ~CircuralDeque() {delete[] buffer;}
    
    bool isEmpty() const
    {
        return size == 0;
    }
    int getSize() const
    {
        return size;    
    }
    
    void push_back(const T& value)
    {
        resize();
        
        if(size == 0)
        {
            front = 0;
            rear = 0;
            buffer[rear] = value;
            size = 1;
            return;
        }
        
        rear = (rear + 1) % capacity;
        buffer[rear] = value;
        ++size;
    }
    void push_front(const T& value)
    {
        resize();
        
        if(size == 0)
        {
            front = 0;
            rear = 0;
            buffer[front] = value;
            size = 1;
            return;
        }
        
        front = (front - 1 + capacity) % capacity;
        buffer[front] = value;
        ++size;
    }
    
    T pop_front()
    {
        if(size == 0)
        {
            throw out_of_range("empty deque");
        }
        
        T val = buffer[front];
        if(size == 1)
        {
            front = -1;
            rear = -1;
            size = 0;
            return val;
        }
        
        front = (front + 1) % capacity;
        --size;
        return val;
    }
    T pop_back()
    {
        if (size == 0)
        {
            throw out_of_range("empty deque");
        }
        
        T val = buffer[rear];
        if (size == 1)
        {
            front = -1;
            rear = -1;
            size = 0;
            return val;
        }
        
        rear = (rear - 1 + capacity) % capacity;
        --size;
        return val;
    }
    
    const T& front_elem() const
    {
        if (size == 0)
        {
            throw out_of_range("front from empty deque");
        }
        return buffer[front];
    }

    const T& back_elem() const
    {
        if (size == 0)
        {
            throw out_of_range("back from empty deque");
        }
        return buffer[rear];
    }
    
    T& operator[](int index)
    {
        if (index < 0 || index >= size)
        {
            throw out_of_range("index out of range");
        }
        return buffer[(front + index) % capacity];
    }

    const T& operator[](int index) const
    {
        if (index < 0 || index >= size)
        {
            throw out_of_range("index out of range");
        }
        return buffer[(front + index) % capacity];
    }
};

int main()
{
    return 0;
}