#include<bits/stdc++.h>
using namespace std;
typedef int64_t ll;
typedef vector<int> vi;
#define mp make_pair
#define pb push_back
#define f first
#define s second
#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) "LAMELO > MJ"
#endif

//RMRC 2021 - M

//josh priority queue greedy implementation. 

//idea is to greedily take nodes in descending order. 

void printPQ(priority_queue<array<ll,2>, vector<array<ll,2>>, greater<array<ll,2>>> pq) {

    cout << "printing pq" << '\n';
    while(pq.size()) {
        cout << pq.top()[0] << " " << pq.top()[1] << " ";
        pq.pop();
    }
    cout << '\n';
}


int main(){
    ios_base::sync_with_stdio(0); 
    cin.tie(0);

    int n; cin >> n;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int p; cin >> p;
        p--;
        adj[i].push_back(p);
        adj[p].push_back(i);
    }

    vector<ll> b(n), v(n);
    for(ll &x : b) cin >> x;
    for(ll &x : v) cin >> x;

    vector<priority_queue<array<ll,2>, vector<array<ll,2>>, greater<array<ll,2>>>> dp(n);

    auto dfs = [&](auto self, int i, int p, ll pv) -> void {
        // v[i] += pv;
        int largestc = -1;
        for(int c : adj[i]) {
            if(c != p) {
                self(self, c, i, v[i]);
                if(largestc == -1 || dp[c].size() > dp[largestc].size()) {
                    largestc = c;
                }
            }
        }
        if(largestc != -1) {
            swap(dp[largestc],dp[i]);
        }
        dp[i].push({v[i],i});

        for(int c : adj[i]) {
            if(c != p && c != largestc) {
                while(dp[c].size()) {
                    dp[i].push(dp[c].top());
                    dp[c].pop();
                }
            }
        }

        // cout << "i : " << i << " ";
        // printPQ(dp[i]);

        while(dp[i].size() > b[i]) {
            dp[i].pop();
        }

    };

    dfs(dfs, 0, -1, 0);

    ll ans = 0;
    vector<int> cities;
    while(dp[0].size()) {
        ans += dp[0].top()[0];
        cities.push_back(dp[0].top()[1]);
        dp[0].pop();
    }

    cout << ans << '\n';
    cout << cities.size() << " ";
    sort(cities.begin(), cities.end());
    for(int i = 0; i < cities.size(); i++) {
        cout << cities[i] + 1 << " \n"[i == cities.size() - 1];
    }

    // cerr << "make it to end \n";

    cout.flush();
    return 0;
}