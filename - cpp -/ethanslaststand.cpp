#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//TAMU Spring 2023 Programming Contest E

//hyping someone up is the same as replacing your number of pushups with theirs. 

//thus, if there is someone that comes after you that can do more pushups, then you should hype them up. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<ll> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    ll ans = 0;
    ll max = 0;
    for(int i = n - 1; i >= 0; i--){
        max = std::max(a[i], max);
        ans += max;
    }
    cout << ans << "\n";
    
    return 0;
}
