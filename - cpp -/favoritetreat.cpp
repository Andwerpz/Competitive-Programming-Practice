#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//UTPC 03-01-24 Div.2 - H

//since n <= 20, we can just do bitset dp. 
//for every state, we can simply try all combinations of two cookies that bob can select. 
//it's always optimal for charlie to eat the tastier treat out of the two. 

vector<ll> dp;
vector<ll> a;
vector<vector<int>> c;
int n;

ll solve(int state) {
    if(dp[state] != -1){
        return dp[state];
    }
    int nr_can_eat = 0;
    vector<bool> can_eat(n, false);
    for(int i = 0; i < n; i++){
        if(((state >> i) & 1) == 0) {
            continue;
        }
        int nr_conn = 0;
        for(int j = 0; j < c[i].size(); j++){
            int next = c[i][j];
            if(((state >> next) & 1) != 0){
                nr_conn ++;
            }
        }
        if(nr_conn == 1){
            can_eat[i] = true;
            nr_can_eat ++;
        }
    }
    dp[state] = 0;
    if(nr_can_eat != 0){
        dp[state] = 0;
        //try all pairs bruh
        vector<int> eats;
        for(int i = 0; i < n; i++){
            if(can_eat[i]) {
                eats.push_back(i);
            }
        }
        for(int i = 0; i < eats.size(); i++){
            for(int j = i + 1; j < eats.size(); j++){
                ll u = a[eats[i]];
                ll v = a[eats[j]];
                if(u > v) {
                    swap(u, v);
                }
                int n_state = state ^ (1 << eats[i]) ^ (1 << eats[j]);
                dp[state] = max(dp[state], u + solve(n_state));
            }
        }
    }
    return dp[state];
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    a = vector<ll>(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    dp = vector<ll>((1 << n), -1);
    c = vector<vector<int>>(n, vector<int>(0));
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        u --;
        v --;
        c[u].push_back(v);
        c[v].push_back(u);
    }
    cout << solve((1 << n) - 1) << "\n";
    
    return 0;
}
