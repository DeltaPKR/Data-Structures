#include <iostream>

using namespace std;

template<typename... Args>
auto sum(Args... args)
{
    return (args + ...);
}

template<typename T>
T maxElement(T a)
{
    return a;
}

template<typename T, typename... Args>
T maxElement(T a, Args... args)
{
    T max = maxElement(args...);
    return (a > max ? a : max); 
}

template<typename T>
int CountArgs(T a)
{
    return 1;
}

template<typename T, typename... Args>
int CountArgs(T a, Args... args)
{
    int count = CountArgs(args...);
    return ++count;
}

string makeSentence(const string& s)
{
    string res = s;
    if(res.empty() || res.back() != '.')
    {
        res.push_back('.');
    }
    return res;
}

template<typename... Rest>
string makeSentence(const string& first, const Rest&... rest)
{
    string tail = makeSentence( rest... );
    
    if(!tail.empty() && tail.back() == '.')
    {
        tail.pop_back();
    }
    string res = first;
    
    if(!tail.empty())
    {
        res += " " + tail;
    }
    res.push_back('.');
    return res;
}

class Logger
{
    int indent;
public:
    Logger(int ind)
    {
        indent = ind;
    }

    void log() const
    {
        
    }

    template<typename T, typename... Args>
    void log(const T& first, const Args&... args)
    {
        cout << string(indent, ' ' ) << first << endl;
        log(args...);
    }
};

template<typename F>
void applyAndPrint(F)
{
    
}

template<typename F, typename T, typename... Args>
void applyAndPrint(F f, T t, Args... args)
{
    cout << f(t) << endl;
    applyAndPrint(f, args...);
}

template<typename A, typename B>
auto makePairList(A a, B b)
{
    return pair(a, b);
}

template<typename A, typename B, typename... Rest>
auto makePairList(A a, B b, Rest... rest)
{
    using Second = decltype(makePairList( b, rest...));
    return pair(a, makePairList(b, rest...));
}

template<typename T>
void printOne(T&& val)
{
    cout << val << " [" << (is_lvalue_reference_v<T> ? "lvalue" : "rvalue" ) << "]" << endl;
}

template<typename... Args>
void betterPrint(Args&&... args)
{
    (printOne(forward<Args>(args)), ...);
}

template<typename T, typename... Args>
T makeObject(Args&&... args)
{
    return T(forward<Args>(args)...);
}

class Person 
{
public:
    string name;
    int age;

    Person(string n, int a) : name(move(n)), age(a) {}
};

int square(int x)
{
    return x * x;
}

int main()
{
    return 0;
}