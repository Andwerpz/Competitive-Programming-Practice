#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1890A

//a good array consists of two alternating values, or just one value. 

//just check whether there exists only two values, and if the difference between the frequencies is
//at most 1. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n);
        int mn = 1e9;
        int mx = -1e9;
        int mn_cnt = 0;
        int mx_cnt = 0;
        for(int i = 0; i < n; i++){
            cin >> a[i];
            mn = min(mn, a[i]);
            mx = max(mx, a[i]);
        }
        for(int i = 0; i < n; i++){
            if(a[i] == mn) {
                mn_cnt ++;
            }
            if(a[i] == mx) {
                mx_cnt ++;
            }
        }
        if(mn == mx) {
            cout << "Yes\n";
            continue;
        }
        if(mn_cnt + mx_cnt != n) {
            cout << "No\n";
            continue;
        }
        if(abs(mn_cnt - mx_cnt) <= 1) {
            cout << "Yes\n";
            continue;
        }
        cout << "No\n";
    }
    
    return 0;
}
