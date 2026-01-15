#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef vector<int> vi;
typedef pair<int, int> pii;

// ICPC PACNW 2025 - F

//observe that the maximum amount of toys for any child is capped to 50. This is probably important. 

//first, we can keep track for each amount in range [0, 50], how many children have that amount of toys. 
//next, for each child, we'll also keep track for each amount in [0, 50], how many of their friends have that amount.

//handling 'F' and 'Q' queries become relatively straightforwards, for F we just have to update the two respective counts
//for 'Q', we can just cross reference the given child's counts with the global count, and stop at the first discrepancy. 

//the only problematic update is 'A', as we need to update the counts of all the given childs friends. 
//at first glance, this seems like it'll TLE, however observe that an edge will only be 'updated across' at most 100 times, 
//as the two children connected across the edge can collectively only recieve up to 100 toys. 
//so actually this runs in linear time WRT Q. 

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, q;
    cin >> n >> q;
    vi f(51, 0);
    f[0] = n;
    vector<vi> cf(n, vi(51, 0));
    vi toy(n, 0);
    vector<vi> c(n);
    while(q--) {
        string t;
        cin >> t;
        if(t == "F") {  
            int u, v;
            cin >> u >> v;
            u --, v --;
            cf[u][toy[v]] ++;
            cf[v][toy[u]] ++;
            c[u].push_back(v);
            c[v].push_back(u);
        }
        else if(t == "A") {
            int u;
            cin >> u;
            u --;
            for(int x : c[u]) {
                cf[x][toy[u]] --;
                cf[x][toy[u] + 1] ++;
            }
            f[toy[u]] --;
            f[toy[u] + 1] ++;
            toy[u] ++;
        }
        else if(t == "Q") {
            int u;
            cin >> u;
            u --;
            int ans = -1;
            // cout << "CHILD : " << u << "\n";
            // for(int i = 0; i <= 50; i++) {
            //     cout << cf[u][i] << " ";
            // }
            // cout << "\n";
            f[toy[u]] --;
            for(int i = 50; i >= 0; i--) {
                if(cf[u][i] != f[i]) {
                    assert(cf[u][i] < f[i]);
                    ans = i;
                    break;
                }
            }
            f[toy[u]] ++;
            cout << ans << "\n";
        }
        else assert(0);
    }

    return 0;
}