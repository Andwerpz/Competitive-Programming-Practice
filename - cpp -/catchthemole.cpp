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
// typedef __int128 lll;
// typedef __float128 lld;

//Codeforces - 1990 E1, E2

//we can keep track of where the mole could be using mark, mark[i] is true if the mole could be at node i.
//next, msum[i] is the amount of marked nodes in the subtree i. Note that if msum[0] == 1, then we're done
//as there is only 1 marked node in the tree. 

//then, for each query, we find the subtree that is closest to having half of the marked nodes in it. 
//if the subtree contains the mole, then unmark everything outside, otherwise unmark everything inside, and
//move the marks up, accounting for the mole moving. Note that when the mole moves, the number of marked
//nodes can only decrease. 

//Ideally, if we half the amount of marked nodes everytime, we should be done in log(n) steps, but it's 
//not guaranteed that there exists a node that has half of the marked nodes in it's subtree. My suspicion
//is that the complexity is closer to sqrt(n) steps.

void calc_msum(int cur, int p, vvi& c, vb& mark, vi& msum){
    msum[cur] = mark[cur];
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p){
            continue;
        }
        calc_msum(next, cur, c, mark, msum);
        msum[cur] += msum[next];
    }
}

void upd_mark(int cur, int p, vvi& c, vb& mark, int x, bool set) {
    if(cur == x){
        set = !set;
    }
    mark[cur] = mark[cur] && set;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p){
            continue;
        }
        upd_mark(next, cur, c, mark, x, set);
    }
}

void move_mole(int cur, int p, vvi& c, vb& mark) {
    if(cur != 0){
        mark[cur] = false;
    }
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p){
            continue;
        }
        mark[cur] = mark[cur] | mark[next];
        move_mole(next, cur, c, mark);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vvi c(n);
        for(int i = 0; i < n - 1; i++){
            int u, v;
            cin >> u >> v;
            u --;
            v --;
            c[u].push_back(v);
            c[v].push_back(u);
        }
        vb mark(n, true);
        vi msum(n, 0);
        while(true){
            calc_msum(0, -1, c, mark, msum);
            if(msum[0] == 1){
                break;
            }
            int tot = msum[0];
            int x = -1;
            for(int i = 0; i < n; i++){
                if(msum[i] && (x == -1 || abs((tot / 2) - msum[i]) < abs((tot / 2) - msum[x]))) {
                    x = i;
                }
            }
            cout << "? " << x + 1 << endl;
            int here;
            cin >> here;    
            if(here) {
                upd_mark(0, -1, c, mark, x, !here);
            }
            else {
                upd_mark(0, -1, c, mark, x, !here);
                move_mole(0, -1, c, mark);
            }
        }
        int ans = -1;
        for(int i = 0; i < n; i++){
            if(mark[i]){
                ans = i;
            }
        }
        cout << "! " << ans + 1 << endl;
    }
    
    return 0;
}