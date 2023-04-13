#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1397B

//since the values of the power sequence go up so fast, you can brute force it. 

//just be careful of overflows, since you are multiplying. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<ll> a(n);
    ll ans = 0;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        ans += a[i] - 1;
    }
    sort(a.begin(), a.end());
    ll c = 1;
    while(n < 40) {
        ll ptr = 1;
        ll cost = 0;
        for(int i = 0; i < n; i++){
            cost += abs(ptr - a[i]);
            ptr *= c;
            if(ptr < 0){
                break;
            }
        }
        if(ptr < 0){
            break;
        }
        if(cost <= ans) {
            ans = cost;
            c ++;
        }
        else {
            break;
        }
    }
    cout << ans << "\n";
    
    return 0;
}
