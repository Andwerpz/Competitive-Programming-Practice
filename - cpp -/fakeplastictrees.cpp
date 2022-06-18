#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1694D

//note that each leaf node requires exactly 1 operation to satisfy. 

//if we have a node i, and it's children j[], then we can use the required operations by j[]
//to satisfy i. Note that the sum from j[] can only be equal to the sum of j[]'s maximum 
//bounds, since the added array has to be non-decreasing. 

//if the sum from j[] is less than the min for i, then we need to use an extra operation to 
//satisfy i. 

int ans;

ll solve(vector<vector<int>> &c, vector<pair<int, int>> &b, int i){
    if(c[i].size() == 0){
        //cout << "Leaf\n";
        ans ++;
        return b[i].second;
    }
    //cout << "Node\n";
    ll out = 0;
    for(int j : c[i]){
        out += solve(c, b, j);
    }
    if(out < b[i].first || out > b[i].second){
        ans += out < b[i].first;
        out = b[i].second;
    }
    return out;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<vector<int>> c(n, vector<int>(0));
        for(int i = 1; i < n; i++){
            int a;
            cin >> a;
            c[--a].push_back(i);
        }
        vector<pair<int, int>> b(n);
        for(int i = 0; i < n; i++){
            cin >> b[i].first >> b[i].second;
        }
        ans = 0;
        solve(c, b, 0);
        cout << ans << "\n";
    }
    
    return 0;
}
