/*
    So, which of the favours
    of your Lord would you deny?
*/

#include <iostream>

#ifdef LOCAL
#include "dbg.h"
#else
#define dbg(...){}
#endif

using namespace std;
using ll = long long;

int a[100005], tree[4*100005], lazy[4*100005];

void init(int node, int start, int end)
{
    if(start > end)
        return;
    if(start == end)
    {
        tree[node] = a[start];
        return;
    }
    int mid = (start + end)/2;
    int left = node * 2, right = node * 2 + 1;
    init(left, start, mid);
    init(right, mid+1, end);
    tree[node] = tree[left] + tree[right];
}

ll query(int node, int start, int end, int i, int j, ll carry = 0)
{
    if(start > j or end < i)
        return 0;
    if(start >= i and end <= j)
        return tree[node] + carry * (end-start+1);
    int mid = (start + end)/2;
    int left = node * 2, right = node * 2 + 1;
    ll left_val = query(left, start, mid, i, j, carry + lazy[node]);
    ll right_val = query(right, mid+1, end, i, j, carry + lazy[node]);
    return left_val + right_val;
}

void update(int node, int start, int end, int i, int j, ll val)
{
    if(start > j or end < i)
        return;
    if(start >= i and end <= j)
    {
        lazy[node] += val;
        tree[node] += val * (end - start + 1);
        return;
    }
    int mid = (start + end)/2;
    int left = node * 2, right = node * 2 + 1;
    update(left, start, mid, i, j, val);
    update(right, mid+1, end, i, j, val);
    tree[node] = tree[left] + tree[right] + lazy[node] * (end - start + 1);
}

int main()
{
    int n;
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> a[i+1];
    init(1,1,n);
    int q;
    cin >> q;
    while(q--)
    {
        int type;
        cin >> type;
        if(type == 0)
        {
            int i, j;
            cin >> i >> j;
            cout << query(1, 1, n, i, j) << "\n";
        }
        else
        {
            int i, j;
            ll val;
            cin >> i >> j >> val;
            update(1, 1, n, i, j, val);
        }
    }
    return 0;
}