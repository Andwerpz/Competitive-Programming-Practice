#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Kattis - codecleanups

//implementation. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<bool> d(365, false);
    for(int i = 0; i < n; i++){
        int next;
        cin >> next;
        next --;
        d[next] = true;
    }
    int dsum = 0;
    int dcnt = 0;
    int ans = 0;
    for(int i = 0; i < 365; i++){
        dcnt += d[i];
        if(dsum + dcnt >= 20){
            ans ++;
            dsum = 0;
            dcnt = 0;
        }
        dsum += dcnt;
    }
    if(dcnt != 0){
        ans ++;
    }
    cout << ans << "\n";
    
    return 0;
}
