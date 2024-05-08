#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Kattis - digits

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    string s;
    cin >> s;
    while(s != "END") {
        if(s == "1"){
            cout << 1 << "\n";
            cin >> s;
            continue;
        }
        int ans = 1;
        int cur = s.size();
        while(true) {
            ans ++;
            int next = to_string(cur).size();
            if(next == cur){
                break;
            }
            cur = next;
        }
        cout << ans << "\n";
        cin >> s;
    }
    
    return 0;
}
