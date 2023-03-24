#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 08 D

//once you read the problem, it's very easy. 

//two prizes cannot use the same sticker, or one sticker cannot be required for more than one prize. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n, m;
        cin >> n >> m;
        vector<vector<ll>> a(n, vector<ll>(0));
        vector<ll> c(n);
        ll ans = 0;
        vector<ll> b(m);
        for(int i = 0; i < n; i++){
            int k;
            cin >> k;
            for(int j = 0; j < k; j++){
                int next;
                cin >> next;
                next --;
                a[i].push_back(next);
            }
            cin >> c[i];
        }
        for(int i = 0; i < m; i++){
            cin >> b[i];
        }
        for(int i = 0; i < n; i++){
            ll min = INT32_MAX;
            for(int j = 0; j < a[i].size(); j++){
                min = std::min(min, b[a[i][j]]);
            }
            ans += min * c[i];
        }
        cout << ans << "\n";
    }
    
    return 0;
}
