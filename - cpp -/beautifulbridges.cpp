#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

ld distSq(pair<ld, ld>& a, pair<ld, ld>& b) {
    return pow(abs(a.first - b.first), 2) + pow(abs(a.second - b.second), 2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    ll h, a, b;
    cin >> n >> h >> a >> b;
    vector<pair<ll, ll>> gint(n, {0, 0});
    vector<pair<ld, ld>> ground(n, {0, 0});
    for(int i = 0; i < n; i++){
        cin >> gint[i].first >> gint[i].second;
        ground[i].first = gint[i].first;
        ground[i].second = gint[i].second;
    }
    vector<ld> max_rd(n, 0);
    vector<ld> max_ld(n, 0);
    //maximum diameter to the left
    for(int i = 0; i < n; i++){
        ld low = 0;
        ld high = h * 2 + 10;
        while(high - low > 1e-6) {
            ld mid = low + (high - low) / 2;
            pair<ld, ld> center = {ground[i].first - mid / 2, h - mid / 2};
            bool isValid = true;
            for(int j = i; j >= 0; j--){
                if(ground[j].first < center.first) {
                    break;
                }
                if(ground[j].second < center.second) {
                    continue;
                }
                if(pow(mid / 2, 2) < distSq(center, ground[j])) {
                    isValid = false;
                    break;
                }
            }
            if(isValid) {
                low = mid;
            }
            else {
                high = mid;
            }
        }
        max_ld[i] = high;
    }
    //maximum diameter to the right
    for(int i = 0; i < n; i++){
        ld low = 0;
        ld high = h * 2 + 10;
        while(high - low > 1e-6) {
            ld mid = low + (high - low) / 2;
            pair<ld, ld> center = {ground[i].first + mid / 2, h - mid / 2};
            bool isValid = true;
            for(int j = i; j < n; j++){
                if(ground[j].first > center.first) {
                    break;
                }
                if(ground[j].second < center.second) {
                    continue;
                }
                if(pow(mid / 2, 2) < distSq(center, ground[j])) {
                    isValid = false;
                    break;
                }
            }
            if(isValid) {
                low = mid;
            }
            else {
                high = mid;
            }
        }
        max_rd[i] = high;
    }
    vector<vector<bool>> valid(n, vector<bool>(n, false));
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            ld diameter = ground[j].first - ground[i].first;
            valid[i][j] = max_rd[i] > diameter && max_ld[j] > diameter;
        }
    }
    // for(int i = 0; i < n; i++){
    //     cout << max_ld[i] << " ";
    // }
    // cout << "\n";
    // for(int i = 0; i < n; i++){
    //     cout << max_rd[i] << " ";
    // }
    // cout << "\n";
    // for(int i = 0; i < n; i++){
    //     for(int j = 0; j < n; j++){
    //         cout << valid[i][j] << " ";
    //     }
    //     cout << "\n";
    // }
    ll unv = 1e18;
    vector<ll> dp(n, unv);
    dp[0] = (h - gint[0].second) * a;
    for(int i = 1; i < n; i++){
        for(int j = 0; j < i; j++){
            if(dp[j] == unv) {
                continue;
            }
            if(!valid[j][i]) {
                continue;
            }
            ll diameter = gint[i].first - gint[j].first;
            ll pillar = h - gint[i].second;
            dp[i] = min(dp[i], dp[j] + pillar * a + diameter * diameter * b);
        }
        //cout << dp[i] << "\n";
    }
    if(dp[n - 1] == unv) {
        cout << "impossible\n";
    }
    else {
        cout << dp[n - 1] << "\n";
    }
    
    return 0;
}
