/*
    So, which of the favours
    of your Lord would you deny?
*/

#include <bits/stdc++.h>

#ifdef ADIB_PC
#include "dbg.h"
#else
#define dbg(...){}
#endif

using namespace std;
using ll = long long;

struct node
{
    ll val;
    ll lazy;
    int left, right;
};

node nodes[4*1000006];
int sz;

void reset(int nd)
{
    nodes[nd].left = nodes[nd].right = -1;
    nodes[nd].val = nodes[nd].lazy = 0;
}

int getLeft(int nd)
{
    if(nodes[nd].left == -1)
    {
        nodes[nd].left = sz++;
        reset(nodes[nd].left);
    }
    return nodes[nd].left;
}
int getRight(int nd)
{
    if(nodes[nd].right == -1)
    {
        nodes[nd].right = sz++;
        reset(nodes[nd].right);
    }
    return nodes[nd].right;
}

void update(int nd, int s, int e, int l, int r, ll val)
{
    if(e < l or s > r) return;
    if(s >= l and e <= r)
    {
        nodes[nd].val += val*(e-s + 1);
        nodes[nd].lazy += val;
        return;
    }
    int m = (s + e) / 2;
    update(getLeft(nd), s, m, l ,r, val);
    update(getRight(nd), m+1, e, l, r, val);
    nodes[nd].val = nodes[nodes[nd].left].val + nodes[nodes[nd].right].val + nodes[nd].lazy * (e-s+1);
}

ll query(int nd, int s, int e, int l, int r, ll c)
{
    if(s > r or e < l) return 0;
    if(s >= l and e <= r)
    {
        return nodes[nd].val + c*(e-s+1);
    }
    int m = (s+e)/2;
    c += nodes[nd].lazy;
    return query(getLeft(nd), s, m, l, r, c) + query(getRight(nd), m+1, e, l, r, c);
}

int main()
{
    int n = 5;
    reset(0);
    sz++;
    for(int i = 0 ; i < n; i++)
        update(0, 1, 1000000009, 1, i+1, 1);
    
    for(int i = 1; i <= n; i++)
        for(int j = i; j <= n; j++)
            cout << i << " " << j << " " << query(0, 1, 1000000009, i, j, 0) << "\n";
    return 0;
}