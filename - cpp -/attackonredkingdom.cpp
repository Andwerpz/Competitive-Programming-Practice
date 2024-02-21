#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//Codeforces - 1312F

//Treat each castle independently, and compute the grundy number for each of them. Use sprague-grundy theorem 
//to test whether or not attacking a specific castle with a specific army composition will allow the white king 
//to win. 

//now, how do we quickly compute grundy numbers? Notice that for a given amount of soldiers, A, the grundy number
//only depends on the grundy numbers of the amounts of soldiers [A - 1, A - 5], due to the range of x, y, z. 
//this means that the grundy numbers in the range [A, A + 5) will uniquely determine the grundy numbers of 
//A + 5, which means that they have to be periodic. 

//if we brute force all possible values of x, y, z, we notice that the maximum period is 36, thus we can compute
//grundy numbers in O(1) given some precomputation. 

int x, y, z;
typedef vector<vector<int>> state;
vector<vector<int>> state_log;
int period;

int mex(vector<int>&& a) {
    sort(a.begin(), a.end());
    int ans = 0;
    for(int i = 0; i < a.size(); i++){
        ans += (a[i] == ans);
    }
    return ans;
}

state calc_next_state(state s) {
    int f0 = mex({s[5 - x][0], s[5 - y][1], s[5 - z][2]});
    int f1 = mex({s[5 - x][0], s[5 - z][2]});
    int f2 = mex({s[5 - x][0], s[5 - y][1]});
    state ans = s;
    ans.erase(ans.begin());
    ans.push_back({f0, f1, f2});
    return ans;
}

void state_precalc() {
    state_log.clear();
    map<state, int> m;
    int cnt = 0;
    state cur(5, vector<int>(3, 0));
    while(!m.count(cur)) {
        m.insert({cur, cnt});
        cnt ++;
        state_log.push_back(cur[4]);
        cur = calc_next_state(cur);
    }
    period = cnt - m[cur];
}

int calc_grundy(ll a, int prev) {
    if(a < 0){
        return 0;
    }
    if(a < state_log.size()) {
        return state_log[a][prev];
    }
    ll mult = (a - state_log.size()) / period + 1;
    a -= mult * period;
    return state_log[a][prev];
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n >> x >> y >> z;
        state_precalc();
        vector<ll> a(n);
        int x_sum = 0;
        for(int i = 0; i < n; i++){
            cin >> a[i];
            x_sum ^= calc_grundy(a[i], 0);
        }
        int ans = 0;
        for(int i = 0; i < n; i++){
            x_sum ^= calc_grundy(a[i], 0);
            ans += (x_sum ^ calc_grundy(a[i] - x, 0)) == 0;
            ans += (x_sum ^ calc_grundy(a[i] - y, 1)) == 0;
            ans += (x_sum ^ calc_grundy(a[i] - z, 2)) == 0;
            x_sum ^= calc_grundy(a[i], 0);
        }
        cout << ans << "\n";
    }
    
    return 0;
}
