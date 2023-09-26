#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1882D

//came up with O(20n) solution, which is too slow. 

vector<vector<int>> c;
vector<vector<int>> c_ind;
vector<vector<bool>> bits;

vector<vector<int>> sub_size;   //i : node, j : parent index
vector<vector<vector<ll>>> dp;  //i : node, j : parent index, l : target

int calc_size(int cur, int parent) {
    if(sub_size[cur][parent] != -1) {
        return sub_size[cur][parent];
    }
    int ans = 1;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(i == parent) {
            continue;
        }
        ans += calc_size(next, c_ind[cur][i]);
    }
    sub_size[cur][parent] = ans;
    return ans;
}

ll solve(int cur, int parent, int bit, int tgt) {
    if(dp[cur][parent][tgt] != -1) {
        return dp[cur][parent][tgt];
    }
    bool apply = false;
    if(bits[cur][bit] != tgt) {
        apply = true;
    }
    ll ans = apply? calc_size(cur, parent) : 0;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(i == parent) {
            continue;
        }
        ans += solve(next, c_ind[cur][i], bit, tgt ^ apply);
    }
    dp[cur][parent][tgt] = ans;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        dp = vector<vector<vector<ll>>>(n, vector<vector<ll>>(0));
        sub_size = vector<vector<int>>(n, vector<int>(0));
        bits = vector<vector<bool>>(n, vector<bool>(20, false));
        for(int i = 0; i < n; i++){
            int next;
            cin >> next;
            for(int j = 0; j < 20; j++){
                bits[i][j] = next & 1;
                next >>= 1;
            }
        }
        c = vector<vector<int>>(n, vector<int>(0));
        c_ind = vector<vector<int>>(n, vector<int>(0));
        for(int i = 0; i < n - 1; i++){
            int u, v;
            cin >> u >> v;
            u --;
            v --;
            c_ind[u].push_back(c[v].size());
            c_ind[v].push_back(c[u].size());
            c[u].push_back(v);
            c[v].push_back(u);
            dp[u].push_back(vector<ll>(2, -1));
            dp[v].push_back(vector<ll>(2, -1));
            sub_size[u].push_back(-1);
            sub_size[v].push_back(-1);
        }
        for(int i = 0; i < n; i++){
            dp[i].push_back(vector<ll>(2, -1));
            sub_size[i].push_back(-1);
        }
        vector<ll> ans(n, 0);
        for(int i = 0; i < 20; i++){
            //considering only the ith bit
            ll mul = (1 << i);
            for(int j = 0; j < n; j++){
                ans[j] += solve(j, c[j].size(), i, bits[j][i]) * mul;
            }
            //reset the dp table
            for(int j = 0; j < n; j++){
                for(int k = 0; k < dp[j].size(); k++){
                    dp[j][k][0] = -1;
                    dp[j][k][1] = -1;
                }
            }
        }
        for(int i = 0; i < n; i++){
            cout << ans[i] << " \n"[i == n - 1];
        }
    }
    
    return 0;
}
