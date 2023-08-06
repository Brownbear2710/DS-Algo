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

/*-------------------------- Ordered Set ----------------------------*/
#include "ext/pb_ds/assoc_container.hpp"
#include "ext/pb_ds/tree_policy.hpp"
using namespace __gnu_pbds;
template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// .order_of_key(x)
// .find_by_order(x)
/*-------------------------------------------------------------------*/

/*---------------------------- Min heap -----------------------------*/
template<typename T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
/*-------------------------------------------------------------------*/

/*-------------------------- GP Hash Table -------------------------*/
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
// gp_hash_table<int, int> table;

const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash {
    int operator()(int x) const { return x ^ RANDOM; }
};
/*------------------------------------------------------------------*/



int main()
{
    fast_IO;
    int T = 1;
    cin >> T;
    while(T--)
    {
        
    }
    return 0;
}