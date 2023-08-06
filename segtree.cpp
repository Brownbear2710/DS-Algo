#include <iostream>

using namespace std;
using ll = long long;

int a[100005], tree[4*100005];

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
    int left = node*2, right = node*2+1;
    init(left, start, mid);
    init(right, mid+1, end);
    tree[node] = tree[left] + tree[right];
}

ll query(int node, int start, int end, int i, int j)
{
    if(start > j or end < i)
        return 0;
    if(start >= i and end <= j)
        return tree[node];
    int mid = (start + end)/2;
    int left = node*2, right = node*2+1;
    ll left_val = query(left, start, mid, i, j);
    ll right_val = query(right, mid+1, end, i, j);
    return left_val + right_val;
}

void update(int node, int start, int end, int pos, ll val)
{
    if(start > pos or end < pos)
        return;
    if(start == end and end == pos)
    {
        tree[node] += val;
        return;
    }
    int mid = (start + end)/2;
    int left = node*2, right = node*2+1;
    update(left, start, mid, pos, val);
    update(right, mid+1, end, pos, val);
    tree[node] = tree[left] + tree[right];
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
            int pos;
            ll val;
            cin >> pos >> val;
            update(1, 1, n, pos, val);
        }
    }
    return 0;
}