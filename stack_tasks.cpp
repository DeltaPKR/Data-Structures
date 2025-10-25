#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>

void reverseStack(std::stack<int> s)
{
    std::vector<int> v;
    while (!s.empty())
    {
        v.push_back(s.top());
        s.pop();
    }
    for (int i = (int)v.size() - 1; i >= 0; --i)
    {
        std::cout << v[i] << ' ';
    }
    std::cout << std::endl;
}

std::string reverseString(const std::string& s)
{
    std::stack<char> st;
    
    for (char c : s)
    {
        st.push(c);
    }
    
    std::string res;
    
    while (!st.empty())
    {
        res.push_back(st.top());
        st.pop();
    }
    return res;
}

void removeMiddleRec(std::stack<int>& s, int k)
{
    if (k == 1)
    {
        if (!s.empty()) s.pop();
        return;
    }
    int top = s.top();
    s.pop();
    
    removeMiddleRec(s, k - 1);
    s.push(top);
}

void removeMiddle(std::stack<int>& s)
{
    int n = (int)s.size();
    
    if (n == 0) return;
    
    int k = (n + 1) / 2;
    removeMiddleRec(s, k);
}

bool isPalindrome(const std::string& s)
{
    std::stack<char> st;
    
    for (char c : s)
    {
        st.push(c);
    }
        
    for (char c : s)
    {
        if (st.top() != c) return false;
        st.pop();
    }
    return true;
}

std::string decToBin(int n)
{
    if (n == 0) return "0";
    
    std::stack<int> st;
    
    bool neg = (n < 0);
    
    if (neg) n = -n;
    
    while (n > 0)
    {
        st.push(n % 2);
        n /= 2;
    }
    
    std::string res;
    if (neg) res.push_back('-');
    
    while (!st.empty())
    {
        res.push_back(char('0' + st.top()));
        st.pop();
    }
    return res;
}

std::string removeAdjDupl(const std::string& s)
{
    std::stack<char> st;
    
    for (char c : s)
    {
        if (!st.empty() && st.top() == c)
        {
            st.pop();
        }
        else
        {
            st.push(c);
        }
    }
    
    std::string res;
    
    res.reserve(st.size());
    
    while (!st.empty())
    {
        res.push_back(st.top());
        st.pop();
    }
    
    reverse(res.begin(), res.end());
    return res;
}

bool isBalanced(const std::string& s)
{
    std::stack<char> st;
    for (char c : s)
    {
        if (c == '(' || c == '[' || c == '{')
            st.push(c);
        else if (c == ')' || c == ']' || c == '}')
        {
            if (st.empty()) return false;
            char t = st.top();
            st.pop();
            if ((c == ')' && t != '(') ||
                (c == ']' && t != '[') ||
                (c == '}' && t != '{'))
                return false;
        }
    }
    return st.empty();
}

class BrowserHistory
{
private:
    std::stack<std::string> backStack;
    std::stack<std::string> forwardStack;
    
    std::string curr;
public:
    BrowserHistory() : curr("") {}
    
    void visit(const std::string& url)
    {
        if (!curr.empty()) backStack.push(curr);
        curr = url;
        while (!forwardStack.empty()) forwardStack.pop();
    }
    
    std::string back()
    {
        if (backStack.empty()) return curr;
        forwardStack.push(curr);
        curr = backStack.top();
        backStack.pop();
        return curr;
    }
    std::string forward()
    {
        if (forwardStack.empty()) return curr;
        backStack.push(curr);
        curr = forwardStack.top();
        forwardStack.pop();
        return curr;
    }
    std::string current() const
    {
        return curr;
    }
};

int prec(char op)
{
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

std::string infixToPostfix(const std::string& s)
{
    std::string out;
    std::stack<char> st;
    
    for (size_t i = 0; i < s.size(); ++i)
    {
        char c = s[i];
        if (std::isspace((unsigned char)c)) continue;
        
        if (std::isalnum((unsigned char)c))
        {
            while (i < s.size() && std::isalnum((unsigned char)s[i]))
            {
                out.push_back(s[i]);
                ++i;
            }
            out.push_back(' ');
            --i;
        }
        else if (c == '(')
            st.push(c);
        else if (c == ')')
        {
            while (!st.empty() && st.top() != '(')
            {
                out.push_back(st.top());
                out.push_back(' ');
                st.pop();
            }
            if (!st.empty()) st.pop();
        }
        else
        {
            while (!st.empty() && ((prec(st.top()) > prec(c)) || (prec(st.top()) == prec(c) && c != '^')) && st.top() != '(')
            {
                out.push_back(st.top());
                out.push_back(' ');
                st.pop();
            }
            st.push(c);
        }
    }
    
    while (!st.empty())
    {
        out.push_back(st.top());
        out.push_back(' ');
        st.pop();
    }
    
    if (!out.empty() && out.back() == ' ') out.pop_back();
    return out;
}

int evalPostfix(const std::string& expr)
{
    std::stack<long long> st;
    
    std::istringstream iss(expr);
    std::string token;
    
    while (iss >> token)
    {
        if (std::isdigit((unsigned char)token[0]) || (token.size() > 1 && token[0] == '-'))
        {
            st.push(std::stoll(token));
        }
        else
        {
            long long b = st.top(); st.pop();
            long long a = st.top(); st.pop();
            
            if (token == "+") st.push(a + b);
            else if (token == "-") st.push(a - b);
            else if (token == "*") st.push(a * b);
            else if (token == "/") st.push(a / b);
        }
    }
    return st.empty() ? 0 : st.top();
}

int main()
{
    // THIS IS A TOWER GAME CODE (TASK 7)
/*    std::stack<char> tower;
    std::string line;
    
    while (std::getline(std::cin, line))
    {
        if (line.empty()) continue;
        
        std::istringstream iss(line);
        std::string cmd;
        
        iss >> cmd;
        
        if (cmd == "add")
        {
            char x;
            iss >> x;
            tower.push(x);
        }
        else if (cmd == "remove")
        {
            if (!tower.empty()) tower.pop();
        }
        else if (cmd == "show")
        {
            std::vector<char> v;
            std::stack<char> tmp = tower;
            
            while (!tmp.empty())
            {
                v.push_back(tmp.top());
                tmp.pop();
            }
            
            for (int i = (int)v.size() - 1; i >= 0; --i)
            {
                std::cout << v[i];
                if (i) std::cout << ' ';
            }
            std::cout << std::endl;
        }
    }*/
    
    //THIS IS CODE FOR TASK 9 (UNDO/REDO)
/*  std::stack<std::string> undoStack;
    std::stack<std::string> redoStack;
    std::string current = "";
    std::string line;
    while (std::getline(std::cin, line))
    {
        if (line.empty()) continue;
        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;
        if (cmd == "type")
        {
            std::string chars;
            iss >> chars;
            undoStack.push(current);
            while (!redoStack.empty()) redoStack.pop();
            current += chars;
        }
        else if (cmd == "undo")
        {
            if (!undoStack.empty())
            {
                redoStack.push(current);
                current = undoStack.top();
                undoStack.pop();
            }
        }
        else if (cmd == "redo")
        {
            if (!redoStack.empty())
            {
                undoStack.push(current);
                current = redoStack.top();
                redoStack.pop();
            }
        }
        else if (cmd == "show")
        {
            std::cout << current << '\n';
        }
    }*/
    
    return 0;
}