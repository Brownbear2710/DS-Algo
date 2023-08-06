
#include <bits/stdc++.h>

using namespace std;
using  ll = long long;
using  ull = unsigned long long;

#define MAXN 200005
#define all(x) x.begin(), x.end()

vector<ll> prime;

void sv()
{
    int n = MAXN;
    vector<bool> is_prime(n+1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= n; i++) {
        if (is_prime[i] && (long long)i * i <= n)
        {
            for (int j = i * i; j <= n; j += i)
                is_prime[j] = false;
        }
    }
    for(int i = 2; i <= n; i++)
    {
        if(is_prime[i]) prime.push_back(i);
    }
}
ull mult(ull a, ull b,  ull mod){
    return (__int128)a * b % mod;
}

 ull f( ull x,  ull c,  ull mod) {
    return (mult(x, x, mod) + c) % mod;
}

 ull rho( ull n,  ull x0=2,  ull c=1) {
    ll x = x0;
    ll y = x0;
    ull g = 1;
    while (g == 1) {
        x = f(x, c, n);
        y = f(y, c, n);
        y = f(y, c, n);
        g = __gcd(abs(x - y), (ll) n);
    }
    return g;
}

using u64 = uint64_t;
using u128 = __uint128_t;
u64 binpower(u64 base, u64 e, u64 mod) {
    u64 result = 1;
    base %= mod;
    while (e) {
        if (e & 1)
            result = (u128)result * base % mod;
        base = (u128)base * base % mod;
        e >>= 1;
    }
    return result;
}

bool check_composite(u64 n, u64 a, u64 d, int s) {
    u64 x = binpower(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = (u128)x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
};

bool MillerRabin(u64 n) { // returns true if n is prime, else returns false.
    if (n < 2)
        return false;
    int r = 0;
    u64 d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }
 
    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == a)
            return true;
        if (check_composite(n, a, d, r))
            return false;
    }
    return true;
}

void smolfact(ull n, vector<ull> &v)
{
    int i = 0;
    while(n > 1 and i < prime.size() and prime[i]*prime[i] <= n)
    {
        while(n%prime[i] == 0)
        {
            v.push_back(prime[i]);
            n /= prime[i];
        }
        i++;
    }
    if(n > 1) v.push_back(n);
}

void fact(ull n, vector<ull> &v)
{
    if(n < 100000000)
    {
        smolfact(n, v);
        return;
    }
    if(MillerRabin(n))
    {
        v.push_back(n);
        return;
    }
    while(1)
    {
        ull x = rho(n,rand()%10000+2, rand()%10000+1);
        if(x != n)
        {
            fact(n/x,v);
            fact(x,v);
            break;
        }
    }
}
/*--------- Convex Hull : Graham Scan template by Adib Farhan ---------*/
struct point
{
    ll x, y;
};
bool operator<(point a, point b)
{
    return ((a.x < b.x )|| (a.x == b.x && a.y < b.y));
}
point reff;
ll dist(point a, point b)
{
    return ((a.x-b.x) * (a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}
ll area(point a, point b,  point c)
{
    return ((b.x - a.x) * (c.y - b.y) - (c.x - b.x) * (b.y - a.y));
}
bool cmp(point a, point b)
{
    if(area(reff, a, b) != area(reff, b,a)) return area(reff, a, b) > 0;
    return dist(reff, a) < dist(reff, b);
}
vector<point> convex_hull(const vector<point> &given)
{
    set<point> st;
    vector<point> v;
    for(auto p : given) st.insert(p); ///  selecting unique points
    for(auto p: st) v.push_back(p);
    st.clear();
    reff = {1000000000,1000000000};
    for(auto p: v)
        reff = (p.y < reff.y || p.y == reff.y && p.x < reff.x ) ? p : reff;
    sort(all(v), cmp);
    vector<point> hull;
    if(v.size()) hull.push_back(v[0]);
    for(int i = 1; i < v.size(); i++)
    {
        while(hull.size() > 1)
            if(area(hull[hull.size()-2], hull.back(), v[i]) <= 0) /// Counter Clockwise Convex hull
                hull.pop_back();
            else break;
        hull.push_back(v[i]);
    }
    return hull;
}

/*-------------------------- Line ---------------------------*/
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
    bool intersect_with_segment(point l, point r)
    {
        ll vl = l.y - val(l.x), vr = r.y - val(r.x);
        if(vl > 0) vl = 1;
        else if(vl < 0) vl = -1;
        if(vr > 0) vr = 1;
        else if(vr < 0) vr = -1;
        return vl*vr >= 0;
    }
};