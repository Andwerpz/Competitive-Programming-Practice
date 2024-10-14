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

//KTH Challenge 2022 - F

//my answer here is very jank. I'll cover a better solution. 
//first, do a dfs traversal of the tree, maintaining a list of leaves that you've seen. 

//then, if there are n leaves, then assign leaf i to leaf i + n / 2. 
//the intuition is that every adjacent assignment is going to have to cross over each other. 
//i have no idea how to prove that every node will be reached though. 

void dfs(int cur, int p, vvi& c, vi& lb, vi& leaves, vi& lc) {
    lb[cur] = leaves.size();
    int nc = 0;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p){
            continue;
        }
        nc ++;
        dfs(next, cur, c, lb, leaves, lc);
        lc[cur] += lc[next];
    }
    if(nc == 0){
        lc[cur] = 1;
        leaves.push_back(cur);
    }
}

void dfs2(int cur, int p, vvi& c, vi& lb, vi& leaves, vi& lc, vector<pii>& ans, vi& pu) {
    // cout << "CUR : " << cur << endl;
    // cout << "PU SIZE : " << pu.size() << endl;
    vector<pii> ch(0);
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p){
            continue;
        }
        // cout << "NEXT : " << next << endl;
        ch.push_back({lc[next], next});
    }
    if(ch.size() == 0){
        // cout << "LEAF : " << cur << "\n";
        if(pu.size() != 0){
            // cout << "PU : " << pu[0] << "\n";
            ans.push_back({cur, pu[0]});
        }
        else {
            int other = leaves[0] != cur? leaves[0] : leaves[1];
            ans.push_back({cur, other});
        }
        return;
    }
    // cout << "CH SIZE : " << ch.size() << endl;
    sort(ch.begin(), ch.end());
    reverse(ch.begin(), ch.end());
    int ocnt = pu.size();
    for(int i = 1; i < ch.size(); i++){
        ocnt += ch[i].first;
    }
    // cout << "OCNT : " << ocnt << "\n";
    vi used(ch.size(), 0);
    int last_i;
    for(int i = ch.size() - 1; i > 0 && ocnt > ch[0].first; i--){
        last_i = ch.size() - 1;
        int cur = ch[i].second;
        // cout << "CUR : " << cur << " " << lc[cur] << " " << cur_used << endl;
        while(pu.size() != 0 && used[i] < lc[cur]){
            ans.push_back({leaves[lb[cur] + used[i]], *pu.rbegin()});
            used[i] ++;
            pu.pop_back();
            ocnt -= 2;
            if(ocnt <= ch[0].first && ocnt <= 5) {
                goto done_loop;
            }
        }
        if(i == 1){
            break;
        }
        int next = ch[i - 1].second;
        while(used[i] < lc[cur]) {
            ans.push_back({leaves[lb[cur] + used[i]], leaves[lb[next] + used[i - 1]]});
            used[i] ++;
            used[i - 1] ++;
            ocnt -= 2;
            if(ocnt <= ch[0].first && ocnt <= 5) {
                goto done_loop;
            }
        }
    }
    done_loop: {}
    // cout << "BUILD PU" << "\n";
    for(int i = ch.size() - 1; i > 0; i--){
        int cur = ch[i].second;
        while(used[i] < lc[cur]){
            pu.push_back(leaves[lb[cur] + used[i]]);
            used[i] ++;
        }
    }  
    dfs2(ch[0].second, cur, c, lb, leaves, lc, ans, pu);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    srand(time(NULL));
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
    int not_leaf = -1;
    for(int i = 0; i < n; i++){
        if(c[i].size() == 1){
            //do nothing :)
        }
        else {
            not_leaf = i;
        }
    }
    vi lb(n, 1e9), lc(n, 0), leaves(0);
    dfs(not_leaf, -1, c, lb, leaves, lc);
    vector<pii> ans(0);
    vi pu(0);
    dfs2(not_leaf, -1, c, lb, leaves, lc, ans, pu);
    cout << ans.size() << "\n";
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i].first + 1 << " " << ans[i].second + 1 << "\n";
    }
    
    return 0;
}