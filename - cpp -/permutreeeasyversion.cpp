#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1856E1

//for each node, we want to partition the children as evenly as possible. 
//the answer for each node is just the product of the partition of children, and the total answer
//is the sum of answers for all nodes. 

pair<ll, ll> solve(vector<vector<int>>& c, int cur) {   //ans, size
    //cout << "SOLVING : " << cur << "\n";
    ll ans = 0;
    ll size = 0;
    vector<ll> sizes(c[cur].size(), 0);
    for(int i = 0; i < c[cur].size(); i++){
        pair<ll, ll> nans = solve(c, c[cur][i]);
        ans += nans.first;
        size += nans.second;
        sizes[i] = nans.second;
    }
    size ++;
    vector<bool> dp(size, false);
    dp[0] = true;
    for(int i = 0; i < sizes.size(); i++){
        for(int j = size - 1; j >= 0; j--){
            if(!dp[j] || j + sizes[i] > size) {
                continue;
            }
            dp[j + sizes[i]] = true;
        }
    }
    ll add = 0;
    for(int i = 0; i < dp.size(); i++){
        if(!dp[i]){
            continue;
        }
        add = max(add, i * (size - i - 1));
    }
    //cout << "ADD : " << cur << " " << add << "\n";
    ans += add;
    return {ans, size};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> a(n - 1);
    for(int i = 0; i < n - 1; i++) {
        cin >> a[i];
    }
    vector<vector<int>> c(n, vector<int>(0));
    for(int i = 0; i < n - 1; i++){
        c[a[i] - 1].push_back(i + 1);
    }
    cout << solve(c, 0).first << "\n";
    
    return 0;
}
