#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSES 1646

//basic pfx sum problem. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    vector<ll> pfx(n);
    pfx[0] = a[0];
    for(int i = 1; i < n; i++){
        pfx[i] = pfx[i - 1] + (ll) a[i];
    }
    for(int i = 0; i < q; i++){
        int l, r;
        cin >> l >> r;
        cout << pfx[--r] - (l == 1? 0 : pfx[--l - 1]) << "\n";
    }
    
    return 0;
}
