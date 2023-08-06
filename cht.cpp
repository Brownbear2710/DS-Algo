#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define all(x) x.begin(), x.end()

struct CHT // Static
{
    struct Line
    {
        ll m, c;
        Line(ll _m, ll _c) : m(_m), c(_c) {}
        long double intersect(Line l)
        {
            return (long double)((l.c - c + m - l.m - 1) / (m - l.m));
        }
        ll val(int x)
        {
            return m * x + c;
        }
    };
    deque<pair<Line, ll>> dq;
    void insert(ll m, ll c)
    {
        Line l(m, c);
        while (dq.size() > 1 and dq.back().first.intersect(dq.end()[-2].first) >= dq.back().first.intersect(l))
            dq.pop_back();
        if (dq.empty())
            dq.emplace_back(l, 0);
        else
            dq.emplace_back(l, dq.back().first.intersect(l));
    }

    ll query(ll x)
    {
        auto it = *--upper_bound(all(dq), make_pair(Line(0, 0), x), [&](auto &a, auto &b)
                               { return a.second < b.second; });
        return it.first.val(x);
    }
};
