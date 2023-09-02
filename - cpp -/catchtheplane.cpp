#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2018 A

//for each station, we can compute the probability that if you go there, you'll reach station 1. 

//kinda like dp, but better :))

void insert(map<ll, ld>& m, ll time, ld prob) {
    if(m.find(time) == m.end()) {
        m.insert({time, prob});
        return;
    }
    m.find(time) -> second = max(m.find(time) -> second, prob);
}

ld query(map<ll, ld>& m, ll time) {
    if(m.size() == 0 || m.rbegin() -> first <= time) {
        return 0;
    }
    return m.upper_bound(time) -> second;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int m, n;
    cin >> m >> n;
    ll k;
    cin >> k;
    vector<vector<ll>> edges(m, vector<ll>(4));
    vector<ld> prob(m);
    for(int i = 0; i < m; i++){
        cin >> edges[i][0] >> edges[i][1] >> edges[i][2] >> edges[i][3] >> prob[i];
    }
    vector<map<ll, ld>> dp(n, map<ll, ld>());
    vector<int> sEdge(m);
    for(int i = 0; i < m; i++){
        sEdge[i] = i;
    }
    sort(sEdge.begin(), sEdge.end(), [&] (int a, int b) -> bool {
        return edges[a][2] > edges[b][2];
    });
    //cout << "INSERTING" << endl;
    insert(dp[1], k + 1, 1);
    //cout << "DONE INSERTING" << endl;
    for(int i = 0; i < m; i++){
        int ind = sEdge[i];
        int from = edges[ind][0];
        int to = edges[ind][1];
        ll dep = edges[ind][2];
        ll arrive = edges[ind][3];
        ld p = prob[ind];
        //cout << from << " " << to << " " << dep << " " << arrive << " " << p << endl;
        ld notTakeProb = query(dp[from], dep);
        //take the bus
        ld takeProb = p * query(dp[to], arrive) + (1.0 - p) * notTakeProb;
        insert(dp[from], dep, max(notTakeProb, takeProb));
        //cout << notTakeProb << " " << takeProb << "\n";
    }
    cout << setprecision(10) << fixed << query(dp[0], -1) << "\n";
    
    return 0;
}
