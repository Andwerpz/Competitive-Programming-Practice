#pragma GCC optimize("O3")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1093E

//ok, i followed the idea that the editorial wrote, but i can't get this to not TLE. 

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less_equal<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;

struct FenwickTree {
    int n;
    ordered_set* a;

    FenwickTree(int _n) {
        n = _n;
        a = new ordered_set[n];
    }

    //how many elements are in a[ind] with value in range [l, r)?
    int query(int ind, int l, int r) {
        return max(0, (int) (a[ind].order_of_key(r) - a[ind].order_of_key(l)));
    }

    //gets the sum in range [0, ar)
    int sum(int ar, int l, int r) {
        ar --;
        int ret = 0;
        for(; ar >= 0; ar = (ar & (ar + 1)) - 1)
            ret += query(ar, l, r);
        return ret;
    }

    int sum(int al, int ar, int l, int r) {
        return sum(ar, l, r) - sum(al, l, r);
    }

    void add(int ind, int val) {
        for (; ind < n; ind = ind | (ind + 1))
            a[ind].insert(val);
    }

    void erase(int ind, int val) {
        for (; ind < n; ind = ind | (ind + 1)) {
            int rank = a[ind].order_of_key(val);
            ordered_set::iterator it = a[ind].find_by_order(rank); 
            a[ind].erase(it);
        }
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(n);
    vector<pair<int, int>> inds(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
        a[i] --;
        inds[a[i]].first = i;
    }
    for(int i = 0; i < n; i++){
        cin >> b[i];
        b[i] --;
        inds[b[i]].second = i;
    }
    vector<vector<int>> q(m);
    for(int i = 0; i < m; i++){
        int t;
        cin >> t;
        if(t == 1){
            int la, ra, lb, rb;
            cin >> la >> ra >> lb >> rb;
            q[i] = {t, la, ra, lb, rb};
        }
        else {
            int x, y;
            cin >> x >> y;
            q[i] = {t, x, y};
        }
    }
    FenwickTree ft(n);
    for(int i = 0; i < n; i++){
        ft.add(inds[i].first, inds[i].second);
    }
    for(int i = 0; i < m; i++){
        int type = q[i][0];
        if(type == 1){
            int la = q[i][1], ra = q[i][2], lb = q[i][3], rb = q[i][4];
            la --;
            lb --;
            cout << ft.sum(la, ra, lb, rb) << "\n";
        }
        else {
            int x = q[i][1], y = q[i][2];
            x --;
            y --;
            ft.erase(inds[b[x]].first, inds[b[x]].second);
            ft.erase(inds[b[y]].first, inds[b[y]].second);
            swap(b[x], b[y]);
            inds[b[x]].second = x;
            inds[b[y]].second = y;
            ft.add(inds[b[x]].first, inds[b[x]].second);
            ft.add(inds[b[y]].first, inds[b[y]].second);
        }
    }
    
    return 0;
}