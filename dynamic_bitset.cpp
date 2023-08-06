#include <bits/stdc++.h>

using namespace std;

using ull = unsigned long long;
class MyBitset
{
private:
    vector<ull> b;
    int n;

public:
    MyBitset(int _n) : n(_n)
    {
        int sz = ceil(n / 64.0);
        b.resize(sz);
    }
    void resize(int _n)
    {
        int n = _n;
        int sz = ceil(n / 64.0);
        b.resize(n);
    }
    void flip()
    {
        for (auto &e : b)
            e = ~e;
        for (int i = n; i < 64 * b.size(); i++)
        {
            set(i, 0);
        }
    }
    int count()
    {
        int cnt = 0;
        for (auto e : b)
        {
            cnt += __builtin_popcount(e);
        }
        return cnt;
    }
    void set(int pos, bool val)
    {
        int x = pos / 64, y = pos % 64;
        if (val)
            b[x] = b[x] | (1ULL << y);
        else
            b[x] = b[x] & ~(1ULL << y);
    }
    void reset()
    {
        for (auto &e : b)
            e = 0;
    }
    bool get(int pos)
    {
        int x = pos / 64, y = pos % 64;
        return b[x] & (1ULL << y);
    }
    int size() { return n; }
    MyBitset operator|(MyBitset &bi)
    {
        MyBitset tmp(n);
        for (int i = 0; i < b.size(); i++)
        {
            tmp.b[i] = b[i] | bi.b[i];
        }
        return tmp;
    }
    MyBitset operator&(MyBitset &bi)
    {
        MyBitset tmp(n);
        for (int i = 0; i < b.size(); i++)
        {
            tmp.b[i] = b[i] & bi.b[i];
        }
        return tmp;
    }
    MyBitset operator^(MyBitset &bi)
    {
        MyBitset tmp(n);
        for (int i = 0; i < b.size(); i++)
        {
            tmp.b[i] = b[i] ^ bi.b[i];
        }
        return tmp;
    }
};
ostream &operator<<(ostream &out, MyBitset &b)
{
    for (int i = 0; i < b.size(); i++)
        out << b.get(i);
    return out;
}

int main()
{
    MyBitset mb1(30), mb2(30);
    MyBitset mb3(12);
    mb1.set(1, 1);
    mb1.set(3, 1);
    mb2.set(3, 1);
    mb2.set(4, 1);
    mb3 = mb1 | mb2;
    cout << mb3 << endl;
    mb3.flip();
    cout << mb3 << endl;
    mb3.reset();
    cout << mb3 << endl;
}