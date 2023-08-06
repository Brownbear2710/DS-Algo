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
#define all(x) begin(x), end(x)
#define MAXN 101

vector<int> adj[MAXN];

struct Centroid_tree
{
    int n;
    vector<int> e[MAXN];
    vector<int> taken, sz, p;
    int root;

    int decompose(int curr, vector<int> adj[])
    {
        calculate_size(curr, -1, adj);
        int r = find_centroid(curr, sz[curr], adj);
        taken[r] = true;
        for(auto child: adj[r])
        {
            if(taken[child]) continue;
            int c = decompose(child,adj);
            p[c] = r;
            e[r].push_back(c);
            e[c].push_back(r);
        }
        return r;
    }
    int calculate_size(int curr, int par, vector<int> adj[])
    {
        int s = 1;
        for(auto child: adj[curr])
            if(!taken[child] and child != par)
                s += calculate_size(child, curr, adj);
        return sz[curr] = s;
    }
    int find_centroid(int curr, int tree_size, vector<int> adj[])
    {
        bool f;
        while(true)
        {
            f = true;
            for(auto nxt: adj[curr])
            {
                if(taken[nxt]) continue;
                if(sz[nxt]*2 > tree_size)
                {
                    f = false;
                    sz[curr] = tree_size-sz[nxt];
                    curr = nxt;
                    break;
                }
            }
            if(f) break;
        }
        return curr;
    }
    Centroid_tree(vector<int> adj[], int _n, int _root = 0) : n(_n)
    {
        taken.resize(n, 0);
        sz.resize(n, 0);
        p.resize(n, 0);
        root = decompose(_root,adj);
    }
};



int main()
{
    fast_IO;
    int n;
    cin >> n;
    for(int i = 0; i < n-1; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    Centroid_tree ct(adj, n+1, 1);
    dbg(ct.root);//!
    cout << "-----------\n";
    for(int i = 1; i <= n; i++)
    {
        cout << i << ": ";
        for(auto e: ct.e[i]) cout << e << " ";
        cout << endl;
    }
    return 0;
}

/*

    1
  / \ \
 2  3  4
      /
     5
    /
   6
  /
 7
n = 7
Input:
7
1 2
1 3
1 4
4 5
5 6
6 7
*/

/*
1 - 2
n = 2
Input:
2
1 2
*/