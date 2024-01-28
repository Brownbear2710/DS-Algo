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

#define MAXN 1000006
#define MOD 1000000007

struct Lz
{
	//! Member Var
	ll update;
	bool operator==(Lz l) { return l.update == update; }
};
struct Tr
{
	//! Member Var
	ll val;
	//! Operator(+) overload for combinig results
	Tr operator+(Tr t) { return Tr{t.val + val}; }
	Tr operator%(int m) { return Tr{val % m}; }
};


int n;
ll a[MAXN];
Tr tree[4*MAXN];
Lz lazy[4*MAXN];
const Tr TNone = {0}; //! Update According to member variables
const Lz LNone = {0}; //! Update According to member variables
// Lazy for child and tree for current
inline void apply(int node, ll s, ll e, Lz u)
{
	if(u == LNone) return;
	//! update tree[node] and lazy[node] by 'u'
}
inline void push_down(int node, int s, int e)
{
	if(s == e) return;
	apply(node<<1, s, s+e >> 1, lazy[node]);
	apply(node<<1|1, s+e+2 >> 1, e, lazy[node]);
	lazy[node] = LNone;
}
void init(int node, int s, int e)
{
    if(s > e) return;
    lazy[node] = LNone;
    if(s == e)
    {
        tree[node] = Tr{a[s]};
        return;
    }
    init(node<<1, s, s+e >> 1);
    init(node<<1|1, s+e+2 >> 1, e);
    tree[node] = (tree[node<<1] + tree[node<<1|1]) % MOD;
}

void update(int node, int s, int e, int i, int j, Lz u)
{
    if(s > j or e < i) return;
	if(s >= i and e <= j)
	{
		apply(node, s, e, u);
		return;
	}
	push_down(node,s,e);
	update(node<<1, s, s+e >> 1, i, j, u);
	update((node<<1) + 1, s+e+2 >> 1, e, i, j, u);
	tree[node] = (tree[node<<1] + tree[node<<1|1]) % MOD;
}

Tr query(int node, int s, int e, int i, int j)
{
    if(s > j or e < i) return TNone;
	if(s >= i and e <= j) return tree[node];
	push_down(node, s, e);
	return (query(node << 1, s, s+e >> 1, i, j) + query(node << 1 | 1, s+e+2 >> 1, e, i, j)) % MOD;
}

int main()
{
    int n;
    return 0;
}