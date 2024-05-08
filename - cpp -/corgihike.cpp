#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//UTPC 03-01-24 Div.2 - B

//just brute force, there aren't too many queries

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    vector<int> elevations(n, 0);
    for(int i = 0; i < n; i++) {
        cin >> elevations[i];
    }
    for(int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l --;
        r --;
        if(l > r){
            swap(l, r);
        }
        bool b = true;
        int elevation = max(elevations[l], elevations[r]);
        for(int j = l + 1; j <= r - 1; j++) {
            if(elevations[j] >= elevation) {
                b = false;
                break;
            }
        }
        if(b) cout << "yes\n";
        else cout << "no\n";
    }
    
    return 0;
}