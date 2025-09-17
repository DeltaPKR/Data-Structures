#include <iostream>
#include <vector>
#include <set>

using namespace std;

template <typename T>
void printVector(const vector<T>& v)
{
    cout << "{ ";
    for (size_t i = 0; i < v.size(); ++i)
    {
        cout << v[i];
        if (i + 1 < v.size()) cout << ", ";
    }
    cout << " }" << endl;
}

void createAndFillVector(int N)
{
    vector<int> v(N);
    for (int i = 0; i < N; ++i)
    {
        v[i] = i + 1;
    }
    printVector(v);
    cout << v.size() << " " << v.capacity() << endl;
}

void workWithEmptyVector()
{
    vector<int> v;
    for (int i = 1; i <= 10; ++i)
    {
        v.push_back(i);
        cout << v.size() << " " << v.capacity() << endl;
    }
    printVector(v);
}

vector<int> createVectorFromInput()
{
    vector<int> v;
    int x;
    while (cin >> x && x != 0)
    {
        v.push_back(x);
    }
    return v;
}

int removeElementsGreaterThan(vector<int>& v, int threshold)
{
    int removed = 0;
    while (!v.empty() && v.back() > threshold)
    {
        v.pop_back();
        ++removed;
    }
    return removed;
}

void manageCapacity(vector<int>& v)
{
    cout << v.size() << " " << v.capacity() << endl;
    v.reserve(v.size() + 500);
    for (int i = 1; i <= 500; ++i)
    {
        v.push_back(i);
    }
    cout << v.size() << " " << v.capacity() << endl;
}

template <typename T>
void resizeVector(vector<T>& v, size_t newSize, const T& value)
{
    printVector(v);
    v.resize(newSize, value);
    printVector(v);
}

vector<int> mergeSortedVectors(const vector<int>& a, const vector<int>& b)
{
    vector<int> result;
    result.reserve(a.size() + b.size());
    merge(a.begin(), a.end(), b.begin(), b.end(), back_inserter(result));
    return result;
}

int findSubsequence(const vector<int>& main_vec, const vector<int>& sub_vec)
{
    if (sub_vec.empty()) return 0;
    if (sub_vec.size() > main_vec.size()) return -1;
    for (size_t i = 0; i + sub_vec.size() <= main_vec.size(); ++i)
    {
        bool ok = true;
        for (size_t j = 0; j < sub_vec.size(); ++j)
        {
            if (main_vec[i + j] != sub_vec[j])
            {
                ok = false;
                break;
            }
        }
        if (ok) return static_cast<int>(i);
    }
    return -1;
}

vector<vector<int>> groupAdjacent(const vector<int>& v)
{
    vector<vector<int>> groups;
    if (v.empty()) return groups;
    vector<int> current;
    current.push_back(v[0]);
    for (size_t i = 1; i < v.size(); ++i)
    {
        if (v[i] == current.back())
        {
            current.push_back(v[i]);
        }
        else
        {
            groups.push_back(current);
            current.clear();
            current.push_back(v[i]);
        }
    }
    if (!current.empty()) groups.push_back(current);
    return groups;
}

template <typename T, typename Pred>
vector<T> filterVector(const vector<T>& v, Pred pred)
{
    vector<T> out;
    out.reserve(v.size());
    for (const auto& el : v)
    {
        if (pred(el)) out.push_back(el);
    }
    return out;
}

class DynamicMatrix
{
public:
    DynamicMatrix(size_t rows, size_t cols)
    {
        data.assign(rows, vector<int>(cols, 0));
    }

    int getElement(size_t row, size_t col) const
    {
        return data.at(row).at(col);
    }

    void setElement(size_t row, size_t col, int value)
    {
        data.at(row).at(col) = value;
    }

    void addRow()
    {
        if (data.empty())
        {
            data.push_back(vector<int>(1, 0));
        }
        else
        {
            data.push_back(vector<int>(data[0].size(), 0));
        }
    }

    void addColumn()
    {
        if (data.empty())
        {
            data.push_back(vector<int>(1, 0));
        }
        else
        {
            for (auto& row : data)
            {
                row.push_back(0);
            }
        }
    }

    void print() const
    {
        for (const auto& row : data)
        {
            cout << "{ ";
            for (size_t j = 0; j < row.size(); ++j)
            {
                cout << row[j];
                if (j + 1 < row.size()) cout << ", ";
            }
            cout << " }" << endl;
        }
    }

private:
    vector<vector<int>> data;
};

vector<int> findIntersection(const vector<int>& a, const vector<int>& b)
{
    set<int> sa(a.begin(), a.end());
    set<int> sb(b.begin(), b.end());
    vector<int> res;
    for (int x : sa)
    {
        if (sb.find(x) != sb.end()) res.push_back(x);
    }
    return res;
}

class VectorStats
{
public:
    VectorStats(const vector<double>& v)
    {
        data = v;
    }

    double mean() const
    {
        if (data.empty()) return 0.0;
        double s = 0.0;
        
        for (double val : data)
        {
            s += val;
        }
        return s / static_cast<double>(data.size());
    }   

    double median() const
    {
        if (data.empty()) return 0.0;
        vector<double> tmp = data;
        sort(tmp.begin(), tmp.end());
        size_t n = tmp.size();
        if (n % 2 == 1) return tmp[n / 2];
        return (tmp[n / 2 - 1] + tmp[n / 2]) / 2.0;
    }

    void addValue(double value)
    {
        data.push_back(value);
    }

    void removeValue(double value)
    {
        auto it = find(data.begin(), data.end(), value);
        if (it != data.end()) data.erase(it);
    }

private:
    vector<double> data;
};

int main()
{
    return 0;
}
