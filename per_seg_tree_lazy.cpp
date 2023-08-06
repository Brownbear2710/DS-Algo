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
    int lazy;
    int left, right;
};

node nodes[MAXN];
int sz = 0;
int a[MAXN];

int build(int s, int e)
{
    int curr = sz;
    sz++;
    if(s == e)
    {
        nodes[curr].left = nodes[curr].right = -1;
        nodes[curr].val = a[s];
        nodes[curr].lazy = 0;
        return curr;
    }
    int m = (s + e) / 2;
    nodes[curr].left = build(s, m);
    nodes[curr].right = build(m + 1, e);
    nodes[curr].val = nodes[nodes[curr].left].val + nodes[nodes[curr].right].val;
    return curr;
}

int update(int prev, int s, int e, int l, int r, int val)
{
    if(s > r or e < l) return prev;
    int curr = sz;
    sz++;
    if(s >= l and e <= r)
    {
        nodes[curr].left = nodes[prev].left;
        nodes[curr].right = nodes[prev].right;
        nodes[curr].val = nodes[prev].val + val*(e-s+1);
        nodes[curr].lazy = nodes[prev].lazy + val;
        return curr;
    }
    int m = (s + e) / 2;
    nodes[curr].left = update(nodes[prev].left, s, m, l, r, val);
    nodes[curr].right = update(nodes[prev].right, m+1, e, l, r, val);
    nodes[curr].lazy = nodes[prev].lazy;
    nodes[curr].val = nodes[nodes[curr].left].val + nodes[nodes[curr].right].val + nodes[curr].lazy*(e-s+1);
    return curr;
}

ll query(int nd, int s, int e, int l, int r, ll c)
{
    if(s > r or e < l) return 0;
    if(s >= l and e <= r) return c*(e-s+1) + nodes[nd].val;
    int m = (s+e)/2;
    c += nodes[nd].lazy;
    return query(nodes[nd].left, s, m, l, r, c) + query(nodes[nd].right, m+1, e, l, r, c);
}

/*---------------------------  end  --------------------------*/


int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> roots(n+1);
    for(int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    int k = 0;
    roots[k] = build(1,n);
    while(m--)
    {
        int t;
        cin >> t;
        if(t == 1)
        {
            int l, r;
            cin >> l >> r;
            cout << query(roots[k], 1, n, l ,r, 0) << "\n";
        }
        else if(t == 2)
        {
            int l, r, val;
            cin >> l >> r >> val;
            roots[k+1] = update(roots[k], 1, n, l, r, val);
            k++;
        }
    }
    return 0;
}