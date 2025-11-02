#include <iostream>
#include <forward_list>
#include <list>
#include <iterator>

void list_root(std::forward_list<int>* ls)
{
    std::forward_list<int> even;
    std::forward_list<int> odd;

    for (auto it = ls->begin(); it != ls->end(); ++it)
    {
        if (*it % 2 == 0)
        {
            even.push_front(*it);
        }
        else
        {
            odd.push_front(*it);
        }
    }

    ls->clear();
    auto tail = ls->before_begin();

    for (auto it = odd.begin(); it != odd.end(); ++it)
    {
        ls->insert_after(tail, *it);
        tail++;
    }
    for (auto it = even.begin(); it != even.end(); ++it)
    {
        ls->push_front(*it);
    }
}

template <typename T>
class Zigzag
{
public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;

private:
    std::list<T> a;
    std::list<T> b;
    size_type cnt = 0;
    bool next_to_a = true;
    bool started_with_a = true;

public:
    class iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

    private:
        Zigzag<T>* parent = nullptr;
        typename std::list<T>::iterator it_a;
        typename std::list<T>::iterator it_b;
        size_type consumed = 0;

        bool choose_a() const
        {
            if (parent == nullptr)
            {
                return false;
            }
            auto endA = parent->a.end();
            auto endB = parent->b.end();
            bool a_has = it_a != endA;
            bool b_has = it_b != endB;
            if (!a_has && !b_has)
            {
                return false;
            }
            if (!a_has)
            {
                return false;
            }
            if (!b_has)
            {
                return true;
            }
            bool start_with_a = parent->started_with_a;
            if ((consumed % 2 == 0 && start_with_a) || (consumed % 2 == 1 && !start_with_a))
            {
                return true;
            }
            return false;
        }

    public:
        iterator() = default;

        iterator(Zigzag<T>* p, typename std::list<T>::iterator ia, typename std::list<T>::iterator ib, size_type c)
            : parent(p), it_a(ia), it_b(ib), consumed(c)
        {
        }

        reference operator*() const
        {
            if (parent == nullptr)
            {
                throw std::out_of_range("dereference end iterator");
            }
            if (choose_a())
            {
                return *it_a;
            }
            return *it_b;
        }

        pointer operator->() const
        {
            return std::addressof(operator*());
        }

        iterator& operator++()
        {
            if (parent == nullptr)
            {
                return *this;
            }
            if (choose_a())
            {
                ++it_a;
            }
            else
            {
                ++it_b;
            }
            ++consumed;
            return *this;
        }

        iterator operator++(int)
        {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        friend bool operator==(iterator const& x, iterator const& y)
        {
            if (x.parent != y.parent)
            {
                return false;
            }
            if (x.parent == nullptr)
            {
                return true;
            }
            return x.consumed == y.consumed;
        }

        friend bool operator!=(iterator const& x, iterator const& y)
        {
            return !(x == y);
        }

        friend class Zigzag<T>;
    };

    class const_iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

    private:
        const Zigzag<T>* parent = nullptr;
        typename std::list<T>::const_iterator it_a;
        typename std::list<T>::const_iterator it_b;
        size_type consumed = 0;

        bool choose_a() const
        {
            if (parent == nullptr)
            {
                return false;
            }
            auto endA = parent->a.cend();
            auto endB = parent->b.cend();
            bool a_has = it_a != endA;
            bool b_has = it_b != endB;
            if (!a_has && !b_has)
            {
                return false;
            }
            if (!a_has)
            {
                return false;
            }
            if (!b_has)
            {
                return true;
            }
            bool start_with_a = parent->started_with_a;

            if ((consumed % 2 == 0 && start_with_a) || (consumed % 2 == 1 && !start_with_a))
            {
                return true;
            }
            return false;
        }

    public:
        const_iterator() = default;

        const_iterator(const Zigzag<T>* p, typename std::list<T>::const_iterator ia, typename std::list<T>::const_iterator ib, size_type c)
            : parent(p), it_a(ia), it_b(ib), consumed(c) {}

        reference operator*() const
        {
            if (parent == nullptr)
            {
                throw std::out_of_range("dereference end iterator");
            }
            if (choose_a())
            {
                return *it_a;
            }
            return *it_b;
        }

        pointer operator->() const
        {
            return std::addressof(operator*());
        }

        const_iterator& operator++()
        {
            if (parent == nullptr)
            {
                return *this;
            }
            if (choose_a())
            {
                ++it_a;
            }
            else
            {
                ++it_b;
            }
            ++consumed;
            return *this;
        }

        const_iterator operator++(int)
        {
            const_iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        friend bool operator==(const_iterator const& x, const_iterator const& y)
        {
            if (x.parent != y.parent)
            {
                return false;
            }
            if (x.parent == nullptr)
            {
                return true;
            }
            return x.consumed == y.consumed;
        }

        friend bool operator!=(const_iterator const& x, const_iterator const& y)
        {
            return !(x == y);
        }

        friend class Zigzag<T>;
    };

    iterator begin()
    {
        return iterator(this, a.begin(), b.begin(), 0);
    }

    iterator end()
    {
        return iterator(this, a.end(), b.end(), cnt);
    }

    const_iterator begin() const
    {
        return const_iterator(this, a.cbegin(), b.cbegin(), 0);
    }

    const_iterator end() const
    {
        return const_iterator(this, a.cend(), b.cend(), cnt);
    }

    const_iterator cbegin() const
    {
        return begin();
    }

    const_iterator cend() const
    {
        return end();
    }

    void insert(const T& value)
    {
        if (cnt == 0)
        {
            started_with_a = next_to_a;
        }
        if (next_to_a)
        {
            a.push_back(value);
        }
        else
        {
            b.push_back(value);
        }
        next_to_a = !next_to_a;
        ++cnt;
    }

    iterator find(const T& value)
    {
        for (auto it = begin(); it != end(); ++it)
        {
            if (*it == value)
            {
                return it;
            }
        }
        return end();
    }

    const_iterator find(const T& value) const
    {
        for (auto it = begin(); it != end(); ++it)
        {
            if (*it == value)
            {
                return it;
            }
        }
        return end();
    }

    iterator erase(iterator pos)
    {
        if (pos.parent != this)
        {
            return end();
        }
        if (pos.consumed >= cnt)
        {
            return end();
        }

        bool from_a = pos.choose_a();

        if (from_a)
        {
            auto it = pos.it_a;
            auto after = std::next(it);
            a.erase(it);
            --cnt;
            iterator ret(this, after, pos.it_b, pos.consumed);
            return ret;
        }
        else
        {
            auto it = pos.it_b;
            auto after = std::next(it);
            b.erase(it);
            --cnt;
            iterator ret(this, pos.it_a, after, pos.consumed);
            return ret;
        }
    }

    size_type size() const
    {
        return cnt;
    }

    bool empty() const
    {
        return cnt == 0;
    }
};

template <typename T>
Zigzag<T> merge(const Zigzag<T>& a, const Zigzag<T>& b)
{
    Zigzag<T> res;
    auto ita = a.begin();
    auto itb = b.begin();
    auto enda = a.end();
    auto endb = b.end();
    bool takeA = true;

    while (ita != enda || itb != endb)
    {
        if (takeA)
        {
            if (ita != enda)
            {
                res.insert(*ita);
                ++ita;
            }
            else if (itb != endb)
            {
                res.insert(*itb);
                ++itb;
            }
        }
        else
        {
            if (itb != endb)
            {
                res.insert(*itb);
                ++itb;
            }
            else if (ita != enda)
            {
                res.insert(*ita);
                ++ita;
            }
        }
        takeA =! takeA;
    }
    return res;
}

int main()
{
    return 0;
}
