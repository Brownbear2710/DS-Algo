/*
    So, which of the favours
    of your Lord would you deny?
*/

#include <bits/stdc++.h>

#ifdef ADIB_PC
#include "dbg.h"
#else
#define dbg(...)
#endif

using namespace std;
using ll = long long;

#define fast_IO ios_base::sync_with_stdio(0), cin.tie(NULL);
#define show(x) cout << #x << ": " << x << endl;
#define all(x) x.begin(), x.end()
#define MAXN 200005

/*--------------------------- start --------------------------*/

struct node
{
    int val;
    int left, right;
};

node nodes[MAXN];
int sz = 0;

int build(int s, int e)
{
    int curr = sz;
    sz++;
    if(s == e)
    {
        nodes[curr].left = nodes[curr].right = -1;
        nodes[curr].val = 0;
        return curr;
    }
    int m = (s + e) / 2;
    nodes[curr].left = build(s, m);
    nodes[curr].right = build(m + 1, e);
    nodes[curr].val = nodes[nodes[curr].left].val + nodes[nodes[curr].right].val;
    return curr;
}

int update(int prev, int s, int e, int pos, int val)
{
    int curr = sz;
    sz++;
    if(s == e)
    {
        nodes[curr].left = nodes[curr].right = -1;
        nodes[curr].val = nodes[prev].val + val;
        return curr;
    }
    int m = (s + e) / 2;
    if(pos <= m)
    {
        nodes[curr].left = update(nodes[prev].left, s, m, pos, val);
        nodes[curr].right = nodes[prev].right;
    }
    else
    {
        nodes[curr].right = update(nodes[prev].right, m+1, e, pos, val);
        nodes[curr].left = nodes[prev].left;
    }
    nodes[curr].val = nodes[nodes[curr].left].val + nodes[nodes[curr].right].val;
    return curr;
}

int query(int n1, int n2, int s, int e, int k)
{
    if(s == e) return s;
    int m = (s + e) / 2;
    int vl1 = nodes[nodes[n1].left].val, vl2 = nodes[nodes[n2].left].val;
    if(vl2 - vl1 < k) return query(nodes[n1].right, nodes[n2].right, m+1, e, k - (vl2 - vl1));
    else return query(nodes[n1].left, nodes[n2].left, s, m, k);
}

/*---------------------------  end  --------------------------*/


int main()
{
    int n, m;
    cin >> n >> m;

    vector<int> root(n+1,1);
    vector<int> v(n);
    for(auto &e : v) cin >> e;

    vector<int> tmp(v);
    sort(all(tmp));

    root[0] = build(1,n);

    for(int i = 1; i <= n; i++)
    {
        int pos = lower_bound(all(tmp), v[i-1]) - tmp.begin() + 1;
        root[i] = update(root[i-1], 1, n, pos, 1);
    }
    while(m--)
    {
        int i, j, k;
        cin >> i >> j >> k;
        int pos = query(root[i-1], root[j], 1, n, k);
        cout << tmp[pos-1] << "\n";
    }
    return 0;
}