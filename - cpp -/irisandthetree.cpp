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

//Codeforces - 2006B

//we want to compute the sum of edges on paths 1 -> 2, 2 -> 3, ..., n -> 1. Since the nodes are labeled in a 
//dfs traversal, each each edge is used exactly twice. So if all edges are determined, the answer is simply 2 * w

//However, there will be paths with undetermined edges. If the remaining undetermined sum is 'U', then on a 
//path with an undetermined edge we can simply set the weight to U, and therefore the answer is 
//(w - U) * 2 + U * ucnt where ucnt is the number of paths with undetermined edges. 

//since each edge shows up in exactly 2 paths, we can solve each edge-determining in O(1). 

void calc_range(int cur, vector<set<int>>& c, vector<pii>& range) {
    range[cur] = {cur, cur + 1};
    for(auto i = c[cur].begin(); i != c[cur].end(); i++){
        int next = *i;
        calc_range(next, c, range);
        range[cur].first = min(range[cur].first, range[next].first);
        range[cur].second = max(range[cur].second, range[next].second);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        ll n, w;
        cin >> n >> w;
        vector<set<int>> c(n);
        vi p(n);
        for(int i = 1; i < n; i++){
            cin >> p[i];
            p[i] --;
            c[p[i]].insert(i);
        }
        vector<pii> range(n);
        calc_range(0, c, range);
        int ptr = 0;
        vvi path(n);
        for(int i = 0; i < n; i++){
            int tgt = (i + 1) % n;
            while(tgt < range[ptr].first || tgt >= range[ptr].second) {
                path[i].push_back(ptr);
                ptr = p[ptr];
            }
            while(ptr != tgt) {
                auto j = c[ptr].upper_bound(tgt);
                j --;
                int next = *j;
                path[i].push_back(next);
                ptr = next;
            }
        }
        vvi etop(n);
        vi p_und(n); vl p_sum(n, 0);
        for(int i = 0; i < path.size(); i++){
            p_und[i] = path[i].size();
            for(int j = 0; j < path[i].size(); j++){
                etop[path[i][j]].push_back(i);
            }
        }
        ll n_und = n;
        ll dec_sum = 0;
        for(int i = 0; i < n - 1; i++){
            ll ind, weight;
            cin >> ind >> weight;
            ind --;
            dec_sum += weight;
            for(int j = 0; j < etop[ind].size(); j++){
                int next = etop[ind][j];
                p_und[next] --;
                if(p_und[next] == 0){
                    n_und --;
                }
            }
            ll und_sum = w - dec_sum;
            ll cans = dec_sum * 2 + und_sum * n_und;
            cout << cans << " ";
        }
        cout << "\n";
    }
    
    return 0;
}