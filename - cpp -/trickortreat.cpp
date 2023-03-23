#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 07 E

//ternary search. 

//keep in mind that max of bitonic upwards max functions, eg parabolas, are themselves bitonic. 

ld func(vector<pair<ld, ld>>& a, ld x) {
    ld ans = 0;
    for(int i = 0; i < a.size(); i++){
        ans = max(ans, sqrt(pow(x - a[i].first, 2) + pow(a[i].second, 2)));
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    while(n != 0){
        vector<pair<ld, ld>> a(n, {0, 0});
        for(int i = 0; i < n; i++){
            cin >> a[i].first >> a[i].second;
        }
        ld low = -1e9;
        ld high = 1e9;
        while(high - low > 1e-9) {
            ld c = low + (high - low) / 3.0;
            ld d = low + ((high - low) / 3.0) * 2.0;
            if(func(a, c) < func(a, d)) {
                high = d;
            }
            else {
                low = c;
            }
        }
        cout << fixed << setprecision(10) << low + (high - low) / 2 << " " << func(a, low + (high - low) / 2) << "\n"; 
        cin >> n;
    }
    
    return 0;
}
