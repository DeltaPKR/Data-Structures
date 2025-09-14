#include <iostream>
#include <array>
using namespace std;

array<int, 5>createArray()
{
    array<int, 5> arr = {1, 2, 3, 4, 5};
    return arr;
}

void fillArray(array<int, 7> &array, int val)
{
    for(int i = 0; i < array.size(); i++)
    {
        array[i] = val;
    }
}

template <size_t N>
int countEven(array<int, N> arr)
{
    int count = 0;
    for (size_t i = 0; i < arr.size(); i++)
    {
        if (arr[i] % 2 == 0) count++;
    }
    return count;
}

template <typename T, size_t N>
int findElement(array<T, N> arr, T value)
{
    for (size_t i = 0; i < arr.size(); i++)
    {
        if (arr[i] == value) return i;
    }
    return -1;
}

template <typename T, size_t N>
void reverseArray(array<T, N> &arr)
{
    for (size_t i = 0; i < N / 2; i++)
    {
        swap(arr[i], arr[N - i - 1]);
    }
}

template <typename T, size_t N>
bool compareArrays(array<T, N> a, array<T, N> b)
{
    for (size_t i = 0; i < N; i++)
    {
        if (a[i] != b[i]) return false;
    }
    return true;
}

template <typename T, size_t N, size_t M>
array<T, M> copySubArray(array<T, N> source, size_t start, size_t count)
{
    array<T, M> result{};
    if (start + count <= N)
    {
        for (size_t i = 0; i < count && i < M; i++)
            result[i] = source[start + i];
    }
    return result;
}

class Matrix3x3
{
private:
    array<array<int, 3>, 3> data;

public:
    Matrix3x3(int a1, int a2, int a3,
              int b1, int b2, int b3,
              int c1, int c2, int c3)
    {
        data = {{{a1, a2, a3}, {b1, b2, b3}, {c1, c2, c3}}};
    }

    int getElement(int row, int col) { return data[row][col]; }
    void setElement(int row, int col, int val) { data[row][col] = val; }

    void transpose()
    {
        for (int i = 0; i < 3; i++)
            for (int j = i + 1; j < 3; j++)
                swap(data[i][j], data[j][i]);
    }

    void print()
    {
        for (auto &row : data)
        {
            for (auto &val : row) cout << val << " ";
            cout << endl;
        }
    }

    array<int, 3> &operator[](int index) { return data[index]; }
};

template <typename T, size_t N>
void shiftLeft(array<T, N> &arr, size_t positions)
{
    positions %= N;
    array<T, N> temp = arr;
    for (size_t i = 0; i < N; i++)
        arr[i] = temp[(i + positions) % N];
}

template <typename T, size_t Rows, size_t Cols>
array<array<T, Cols>, Rows> process2DArray(array<array<T, Cols>, Rows> arr, T (*func)(T))
{
    array<array<T, Cols>, Rows> result = arr;
    for (size_t i = 0; i < Rows; i++)
        for (size_t j = 0; j < Cols; j++)
            result[i][j] = func(arr[i][j]);
    return result;
}

template <typename T, size_t N>
bool validateArray(array<T, N> arr, T min, T max)
{
    for (auto &val : arr)
        if (val < min || val > max) return false;
    return true;
}

template <size_t N>
array<int, 256> countFrequency(array<char, N> arr)
{
    array<int, 256> freq{};
    for (auto c : arr)
        freq[(unsigned char)c]++;
    return freq;
}

int doubleVal(int x) { return x * 2; }

int main()
{
    array<int, 6> arr1 = {1, 2, 3, 4, 5, 6};
    cout << "Count of even: " << countEven(arr1) << endl;

    cout << "Find element 4: " << findElement(arr1, 4) << endl;
    cout << "Find element 10: " << findElement(arr1, 10) << endl;

    array<int, 5> arr2 = {1, 2, 3, 4, 5};
    reverseArray(arr2);
    cout << "Reversed array: ";
    for (int x : arr2) cout << x << " ";
    cout << endl;

    array<int, 5> arr3 = {5, 4, 3, 2, 1};
    cout << "Compare arrays: " << compareArrays(arr2, arr3) << endl;

    array<int, 10> source = {1,2,3,4,5,6,7,8,9,10};
    auto sub = copySubArray<int, 10, 5>(source, 2, 5);
    cout << "Subarray: ";
    for (int x : sub) cout << x << " ";
    cout << endl;

    Matrix3x3 matrix(1,2,3,4,5,6,7,8,9);
    cout << "Original matrix:" << endl;
    matrix.print();
    matrix.transpose();
    cout << "Transposed matrix:" << endl;
    matrix.print();
    cout << "Element [1][2]: " << matrix[1][2] << endl;

    array<int, 5> arr4 = {1,2,3,4,5};
    shiftLeft(arr4, 2);
    cout << "Shifted left by 2: ";
    for (int x : arr4) cout << x << " ";
    cout << endl;

    array<array<int,3>,3> matrix2d = {{{{1,2,3}},{{4,5,6}},{{7,8,9}}}};
    auto doubled = process2DArray(matrix2d, doubleVal);
    cout << "Doubled 2D array:" << endl;
    for (auto &row : doubled)
    {
        for (auto val : row) cout << val << " ";
        cout << endl;
    }

    array<int, 4> scores = {85, 92, 78, 96};
    cout << "Validate scores 0-100: " << validateArray(scores, 0, 100) << endl;

    array<char,5> text = {'h','e','l','l','o'};
    auto freq = countFrequency(text);
    cout << "Frequency of 'l': " << freq['l'] << endl;

    return 0;
}
