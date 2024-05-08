#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Kattis - baloni

//nice problem. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> h(n);
    for(int i = 0; i < n; i++){
        cin >> h[i];
    }
    map<int, int> m;
    int ans = 0;
    for(int i = 0; i < n; i++){
        if(m[h[i]] == 0){
            m[h[i]] ++;
            ans ++;
        }
        m[h[i]] --;
        m[h[i] - 1] ++;
    }
    cout << ans << "\n";
    
    return 0;
}
