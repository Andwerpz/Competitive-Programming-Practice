#include <bits/stdc++.h>
typedef long long ll;
// typedef __128 lll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2011 J

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<pair<ll,pair<ll,ll>>> pyramids(0);
    {
        ll curr = 1;
        for(ll i = 2; ; i++) {
            curr += i * i;
            if( curr > 1e6) break;
            pyramids.push_back({curr,{1,i}});
        }
    }
    {
        ll sum = 4;
        ll height = 1;
        for(ll i = 4; ; i += 2) {
            sum += i * i;
            if(sum > 1e6) {
                break;
            }
            height ++;
            pyramids.push_back({sum, {0, i}});
        }
    }
    {
        ll sum = 1;
        ll height = 1;
        for(ll i = 3; ; i += 2){
            sum += i * i;
            if(sum > 1e6) {
                break;
            }
            height ++;
            pyramids.push_back({sum, {0, i}});
        }
    }

    sort(pyramids.begin(),pyramids.end(), [](pair<ll,pair<ll,ll>> &l, pair<ll,pair<ll,ll>> &r) -> bool {
        if(l.first == r.first) {
            return l.second.first > r.second.first;
        } else {
            return l.first > r.first;
        }
    });
    for(int i = 0; i < pyramids.size(); i++){
        cout << pyramids[i].first << " " << pyramids[i].second.first << " " << pyramids[i].second.second << "\n";
    }
    {
        reverse(pyramids.begin(), pyramids.end());
        ll n = 1e6;
        dp_prev[0] = {0, {-1, -1}};
        for(ll i = 0; i < pyramids.size(); i++){
            // dp[0] = {0}
            for(ll j = 0; j <= n; j++){
                dp[j] = dp_prev[j];
                if (pyramids[i].first > j) continue;
                if (dp_prev[j - pyramids[i].first].first + 1 <= dp[j].first) {
                    // update
                    dp[j].first = dp_prev[j - pyramids[i].first].first + 1;
                    dp[j].second.first = j - pyramids[i].first;
                    dp[j].second.second = i;
                }
            }
            swap(dp, dp_prev);
        }
        dp = dp_prev;
    }
    ll n; cin >> n;
    ll caseno = 0;
    while(n) {
        caseno ++;
        // solve(n, pyramids, caseno);
        ll col = -1;
        if(dp[n].first < unv) {
            col = n;
        }
        //cout << "ROW COL : " << col << endl;
        if(col == -1){
            cout << "Case " << caseno << ": impossible\n";
            cin >> n;
            continue;
        }
        vector<pair<ll, pair<ll, ll>>> ans(0);
        while(col != 0){
            ll p_col = dp[col].second.first;
            ll p_ind = dp[col].second.second;
            // cout << "BUILT PYRAMID : " << p_row << " " << p_col << "\n";
            //cout << "BUILT PYRAMID : " << pyramids[p_ind].first << endl;
            ans.push_back({pyramids[p_ind].first, {pyramids[p_ind].second.second, pyramids[p_ind].second.first}});
            col = p_col;
        }
        sort(ans.begin(), ans.end(), [](pair<ll, pair<ll, ll>>& a, pair<ll, pair<ll, ll>>& b) -> bool {
            if(a.first != b.first) {
                return a.first > b.first;
            }
            return a.second.second > b.second.second;
        });
        cout << "Case " << caseno << ": ";
        for(ll i = 0; i < ans.size(); i++){
            cout << ans[i].second.first;
            // cout << " "
            if(ans[i].second.second == 1) {
                cout << "H";
            }
            else {
                cout << "L";
            }
            cout << " ";
            // cout << endl;
        }
        cout << "\n";
        // solve(n, pyramids, caseno);
        cin >> n;

    }
    
    return 0;
}
