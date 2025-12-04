#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl; 
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
// typedef __int128 lll;
// typedef __float128 lld;

//Codeforces - 2168C

//can just use hamming code to directly solve. 
//we just need to transmit 5 extra bits of information to do error detection and correction. 

int hamming_encode(int x) {
    int ret = 0;
    int xptr = 0, xsum = 0;
    for(int i = 1; i <= 20; i++) {
        if(__builtin_popcount(i) == 1) continue;
        if(x & (1 << xptr)) {
            ret |= (1 << (i - 1));
            xsum ^= i;
        }
        xptr ++;
    }   
    for(int i = 0; i < 20; i++) {
        if(xsum & (1 << i)) {
            ret |= (1 << ((1 << i) - 1));
        }
    }
    return ret;
}

int hamming_decode(int x) {
    int ret = 0;
    int xsum = 0;
    for(int i = 1; i <= 20; i++) {
        if(x & (1 << (i - 1))) xsum ^= i;
    }
    if(xsum != 0) {
        x ^= (1 << (xsum - 1));
    }
    int xptr = 0;
    for(int i = 1; i <= 20; i++) {
        if(__builtin_popcount(i) == 1) continue;
        if(x & (1 << (i - 1))) {
            ret |= (1 << xptr);
        }
        xptr ++;
    }
    return ret;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    string run;
    cin >> run;
    if(run == "first") {
        int t;
        cin >> t;
        while(t--) {
            int x;
            cin >> x;
            x --;
            int code = hamming_encode(x);
            vi ans;
            for(int i = 0; i < 20; i++) {
                if(code & (1 << i)) ans.push_back(i + 1);
            }
            cout << ans.size() << "\n";
            for(int i : ans) cout << i << " ";
            cout << "\n";
        }
    }
    else {
        int t;
        cin >> t;
        while(t--) {
            int n;
            cin >> n;
            int code = 0;
            for(int i = 0; i < n; i++){
                int x;
                cin >> x;
                x --;
                code |= (1 << x);
            }
            int x = hamming_decode(code);
            x ++;
            cout << x << "\n";
        }
    }
    
    return 0;
}