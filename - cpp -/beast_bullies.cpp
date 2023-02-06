#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//ICPC North America Qualifier 2022 A

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;

    vector<ll> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    sort(a.rbegin(), a.rend());

    ll att = a[0];
    int ans = 0;
    for (int i = 1; i < n; i += 0) {
        int j = i;
        ll def = 0;
        while (j < n && def < att) {
            def += a[j];
            j++;
        }
        // cerr << "attack : " << att << " def : " << def << endl;
        
        if (def < att) {
            break;
        } else ans = j - 1, att += def;
        i = j;
    }

    cout << ans + 1 << endl;
    
    return 0;
}
