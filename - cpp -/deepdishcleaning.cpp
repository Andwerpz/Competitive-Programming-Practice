#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//UTPC Contest 12-01-23 Div. 1 D

//when cleaning teeth, it's always best to fully use each toothpick before getting another one. 

//notice that the number of teeth <= 10^3. This means that we can just brute force try all starting locations. 

int calc_ans(vector<pair<int, int>>& cost, int s, int p, int start){
    int ans = 1;
    int dur_s = s;
    int dur_p = p;
    for(int i = 0; i < cost.size(); i++){
        int ind = (start + i) % cost.size();
        if(cost[ind].first > dur_s || cost[ind].second > dur_p) {
            dur_s = s;
            dur_p = p;
            ans ++;
        }
        dur_s -= cost[ind].first;
        dur_p -= cost[ind].second;
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t, n;
    cin >> t >> n;
    vector<pair<int, int>> cost(t, {2, 0});
    for(int i = 0; i < n; i++){
        int a, b;
        cin >> a >> b;
        a --;
        b --;
        for(int j = a; j < b; j++){
            cost[j] = {1, 1};
        }
    }
    int s, p;
    cin >> s >> p;
    s *= 2;
    p *= 2;
    int ans = 1e9;
    for(int i = 0; i < t; i++){
        ans = min(ans, calc_ans(cost, s, p, i));
    }
    reverse(cost.begin(), cost.end());
    for(int i = 0; i < t; i++){
        ans = min(ans, calc_ans(cost, s, p, i));
    }
    cout << ans << "\n";
    
    return 0;
}
