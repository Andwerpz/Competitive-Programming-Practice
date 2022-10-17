#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces 643C

//if we can compute an array a where a[i] is the number of xy pairs that have sum i, then for each possible z value, 
//we can compute the number of xy pairs that have greater sum than it as sfx[z + 1]. 

//to construct a, we can use pfx sum range modify techniques. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    vector<ll> pfx(1e6 + 1);
    for(int i = b; i <= c; i++){
        pfx[i + a] ++;
        pfx[i + b + 1] --;
    }
    for(int i = 1; i < pfx.size(); i++){
        pfx[i] += pfx[i - 1];
    }
    ll ans = 0;
    for(int i = pfx.size() - 2; i >= 0; i--){
        pfx[i] += pfx[i + 1];
    }
    for(int i = c; i <= d; i++) {
        ans += pfx[i + 1];
    }
    cout << ans << "\n";
    
    return 0;
}
