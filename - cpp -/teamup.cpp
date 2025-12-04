#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl; 
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
// typedef __int128 lll;
// typedef __float128 lld;

//CodeSprint LA 2025 Open - K

//if a team is given unlimited moves, when can it win? It can win when no other team encloses it, has more
//than 1 player outside of it, and the team itself has more than 1 player. So to check if a team can become
//effectively winning with unlimited moves, we just need to check that these three are true. 

//Checking if the team has more than 1 player is trivial. Checking that no other team encloses it is less
//trivial. We can maintain a segment tree where for each rightmost member of a team it keeps track of
//the index of the leftmost member. Then, if our current team occupies segment [l, r), we can query
//the minimum value of [r, n) in the segment tree and we've found an enclosing team if the value is
//less than l. 

//to check if there exists a team with more than 1 player outside of our team, we can keep track for every 
//team, the second player to the left and to the right in a set. 

//finally, to compute the minimum number of moves, observe that we just need to eliminate all members of 
//other teams inside the segment [l, r) that have some team member outside of the segment. This amount can
//also be maintained using a segment tree. 

template <typename T>
struct Segtree {
    //note that t[0] is not used
    int n;
    T* t;
    T uneut, qneut;
    function<T(T, T)> fmodify, fcombine;

    Segtree() {}
    Segtree(int n, T updateNeutral, T queryNeutral, function<T(T, T)> fm, function<T(T, T)> fc) {
        this->n = n;
        t = new T[2 * n];
        this->fmodify = fm;
        this->fcombine = fc;
        uneut = updateNeutral;
        qneut = queryNeutral;
        for(int i = 0; i < n; i++) t[i + n] = uneut;
        build();
    }

    void assign(vector<T>& arr) {
        for(int i = 0; i < min(n, (int) arr.size()); i++)
            t[i + n] = arr[i];
        build();
    }

	// build the tree after manually assigning the values.
    void build() { 
        for (int i = n - 1; i > 0; i--)
            t[i] = fcombine(t[i * 2], t[i * 2 + 1]);
    }

    void modify(int p, T value) { // set value at position p
        p += n;
        t[p] = fmodify(t[p], value);
        for (p /= 2; p > 0; p /= 2)
            t[p] = fcombine(t[p * 2], t[p * 2 + 1]);
    }

    T query(int l, int r) { // sum on interval [l, r)
        T l_res = qneut, r_res = qneut;
        bool l_none = true, r_none = true;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l % 2 == 1) {
                if(l_none) {l_none = false; l_res = t[l];}
                else l_res = fcombine(l_res, t[l]);
                l++;
            }
            if (r % 2 == 1) {
                r--;
                if(r_none) {r_none = false; r_res = t[r];}
                else r_res = fcombine(t[r], r_res);
            }
        }
        if(l_none) return r_res;
        if(r_none) return l_res;
        return fcombine(l_res, r_res);
    }

    T query(int ind) {
        return this->query(ind, ind + 1);
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    vi a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) a[i] --;
    Segtree<int> segt_sum, segt_min;
    {
        function<int(int, int)> fmodify = [](const int src, const int val) -> int{return val;};
        function<int(int, int)> fcombine = [](const int a, const int b) -> int{return min(a, b);};
        segt_min = Segtree<int>(n, 0, 1e9, fmodify, fcombine);
    }
    {
        function<int(int, int)> fmodify = [](const int src, const int val) -> int{return val;};
        function<int(int, int)> fcombine = [](const int a, const int b) -> int{return a + b;};
        segt_sum = Segtree<int>(n, 0, 0, fmodify, fcombine);
    }
    set<int> l2, r2;    
    vector<set<int>> teams(n);
    function<void(int)> rm_entries = [&](int team) -> void {
        if(teams[team].size() >= 2) {
            auto ptr1 = teams[team].begin();
            ptr1 ++;
            l2.erase(*ptr1);
            auto ptr2 = teams[team].rbegin();
            ptr2 ++;
            r2.erase(*ptr2);
        }
        if(teams[team].size() != 0){
            int l = *teams[team].begin(), r = *teams[team].rbegin();
            segt_min.modify(r, 1e9);
            segt_sum.modify(l, 0);
            segt_sum.modify(r, 0);
        }
    };
    function<void(int)> add_entries = [&](int team) -> void {
        if(teams[team].size() >= 2) {
            auto ptr1 = teams[team].begin();
            ptr1 ++;
            l2.insert(*ptr1);
            auto ptr2 = teams[team].rbegin();
            ptr2 ++;
            r2.insert(*ptr2);
        }
        if(teams[team].size() != 0){
            int l = *teams[team].begin(), r = *teams[team].rbegin();
            segt_min.modify(r, l);
            segt_sum.modify(l, teams[team].size() - 1);
            segt_sum.modify(r, teams[team].size() - 1);
        }
    };
    function<void(int)> rm_player = [&](int player) -> void {
        int ct = a[player];
        rm_entries(ct);
        teams[ct].erase(player);
        add_entries(ct);
        a[player] = -1;
    };  
    function<void(int, int)> add_player = [&](int player, int team) -> void {
        rm_entries(team);
        teams[team].insert(player);
        add_entries(team);
        a[player] = team;
    };
    function<void(int, int)> mv_player = [&](int player, int team) -> void {
        rm_player(player);
        add_player(player, team);
    };
    for(int i = 0; i < n; i++) add_player(i, a[i]);
    while(q--) {
        int type;
        cin >> type;
        if(type == 1){
            int team, pla;
            cin >> team >> pla;
            team --, pla --;
            mv_player(pla, team);
        }
        else {
            int team;
            cin >> team;
            team --;
            if(teams[team].size() <= 1) {
                // cout << "TEAM SIZE : " << teams[team].size() << "\n";
                cout << "-1\n";
                continue;
            }
            int l = *teams[team].begin(), r = *teams[team].rbegin();
            if((l2.size() != 0 && *l2.begin() < l) || (r2.size() != 0 && *r2.rbegin() > r)) {
                // cout << "PFX SFX HAS 2\n";
                cout << "-1\n";
                continue;
            }
            if(segt_min.query(r + 1, n) < l) {
                // cout << "ENCLOSED\n";
                cout << "-1\n";
                continue;
            }
            //can always win
            int ans = segt_sum.query(0, l) + segt_sum.query(r + 1, n);
            cout << ans << "\n";
        }
    }
    
    return 0;
}