#include <iostream>
#include <vector>
#include <cstring>
#include <stdexcept>

using namespace std;

template<typename T>
void printElement(const T& ref)
{
    cout << ref << endl;
}

template<typename T>
void mySwap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}

template<typename T>
T sumArray(T* arr, int size)
{
    T sum = T{};
    for (int i = 0; i < size; ++i)
    {
        sum += arr[i];
    }
    return sum;
}

template<typename T, typename Pred>
vector<T> filter(T* arr, int size, Pred pred)
{
    vector<T> result;
    for (int i = 0; i < size; ++i)
    {
        if (pred(arr[i]))
        {
            result.push_back(arr[i]);
        }
    }
    return result;
}

template<typename T>
int linearSearch(const vector<T>& vec, const T& value)
{
    for (int i = 0; i < vec.size(); ++i)
    {
        if (vec[i] == value) return i;
    }
    return -1;
}

template<typename T1, typename T2>
class Pair
{
public:
    Pair() = default;
    Pair(const T1& a, const T2& b) : first(a), second(b) {}

    void print() const
    {
        cout << "Pair: " << first << " , " << second << endl;
    }

    T1 first;
    T2 second;
};

template<typename T>
class Pair<T, T>
{
public:
    Pair() = default;
    Pair(const T& a, const T& b) : first(a), second(b) {}
    void print() const
    {
        cout << "Pair same type: " << first << " , " << second << endl;
    }
    T first;
    T second;
};

template<typename T, int N>
class FixedArray
{
public:
    FixedArray() = default;
    void set(int index, const T& value)
    {
        if (index < 0 || index >= N)
        {
            throw out_of_range("Index out of range");
        }
        data[index] = value;
    }
    T get(int index) const
    {
        if (index < 0 || index >= N)
        {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }
    int size() const { return N; }
private:
    T data[N]{};
};

template<typename T, int N, int M>
class Matrix
{
public:
    Matrix() = default;

    void set(int row, int col, const T& value)
    {
        if (row < 0 || row >= N || col < 0 || col >= M)
            throw out_of_range("index out of range");
        data[row][col] = value;
    }

    T get(int row, int col) const
    {
        if (row < 0 || row >= N || col < 0 || col >= M)
            throw out_of_range("index out of range");
        return data[row][col];
    }

    void print() const
    {
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < M; ++j)
            {
                cout << data[i][j] << " ";
            }
            cout << endl;
        }
    }

    Matrix<T, N, M> operator+ (const Matrix<T, N, M>& other) const
    {
        Matrix<T, N, M> res;
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < M; ++j)
            {
                res.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return res;
    }

private:
    T data[N][M]{};
};

template<typename T>
class Range
{
public:
    Range(T s, T e) : start(s), end(e) {}

    bool contains(const T& value) const
    {
        return !(value < start) && !(end < value);
    }

    auto length() const
    {
        return end - start;
    }

    void print() const
    {
        cout << "[" << start << " , " << end << "]" << endl;
    }

private:
    T start;
    T end;
};

template<typename T>
void printValue(const T& val)
{
    cout << val << endl;
}

void printValue(const bool& b)
{
    cout << (b ? "true" : "false") << endl;
}

void printValue(const char* s)
{
    if (s)
        cout << '"' << s << '"' << endl;
    else
        cout << "null" << endl;
}

template<typename T>
bool isEqual(const T& a, const T& b)
{
    return a == b;
}

bool isEqual(const char* a, const char* b)
{
    if (a == nullptr && b == nullptr) return true;
    if (a == nullptr || b == nullptr) return false;
    return strcmp(a, b) == 0;
}

template<typename T>
T copyValue(const T& val)
{
    return val;
}

template<typename T>
T* copyValue(T* ptr)
{
    if (!ptr) return nullptr;
    return new T(*ptr);
}

int main()
{
    return 0;
}
