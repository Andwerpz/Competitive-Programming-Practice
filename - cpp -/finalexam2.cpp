#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Kattis - finalexam2

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    int ans = 0;
    vector<string> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    for(int i = 1; i < n; i++){
        if(a[i] == a[i - 1]){
            ans ++;
        }
    }
    cout << ans << "\n";
    
    return 0;
}
