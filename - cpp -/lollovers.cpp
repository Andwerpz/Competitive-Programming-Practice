#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ICPC 2023–2024 NERC L

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    string s;
    cin >> s;
    int tl = 0;
    int to = 0;
    for(int i = 0; i < n; i++){
        tl += s[i] == 'L';
        to += s[i] == 'O';
    }
    int l = 0;
    int o = 0;
    int ans = -1;
    for(int i = 0; i < n - 1; i++){
        l += s[i] == 'L';
        o += s[i] == 'O';
        tl -= s[i] == 'L';
        to -= s[i] == 'O';
        if(l != tl && o != to) {
            ans = i + 1;
            break;
        }
    }
    cout << ans << "\n";
    
    return 0;
}
