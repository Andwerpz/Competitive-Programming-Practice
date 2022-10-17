#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces 276C

//the solution is to compute how many times each index contributes to the sum, and greedily putting the
//greatest value at the greatest contribution. 

//computing the contribution distribution can be done using range modification pfx sum. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    vector<int> pfx(n);
    for(int i = 0; i < q; i++){
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        pfx[l] ++;
        if(r != n - 1){
            pfx[r + 1] --;
        }
    }
    for(int i = 1; i < n; i++){
        pfx[i] += pfx[i - 1];
    }
    sort(pfx.begin(), pfx.end());
    sort(a.begin(), a.end());
    ll ans = 0;
    for(int i = 0; i < n; i++){
        ans += (ll) ((ll)pfx[i] * (ll)a[i]);
    }
    cout << ans << "\n";
    
    return 0;
}
