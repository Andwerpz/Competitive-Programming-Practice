#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Kattis - firefly

//for each height, just figure out how many stalagmites and stalagtites you'll collide with. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, h;
    cin >> n >> h;
    vector<int> a(n / 2), b(n / 2);
    for(int i = 0; i < n; i++){
        if(i % 2 ==0) {
            cin >> a[i / 2];
        }
        else {
            cin >> b[i / 2];
        }
    }
    vector<int> c(h + 1, 0);
    sort(a.begin(), a.end());
    int ptr = 0;
    for(int i = 1; i <= h; i++){
        while(ptr != a.size() && a[ptr] + 1 <= i) {
            ptr ++;
        }
        c[i] += a.size() - ptr;
        // cout << a.size() - ptr << " ";
    }
    // cout << "\n";
    sort(b.begin(), b.end());
    ptr = 0;
    for(int i = h; i >= 1; i--){
        while(ptr != b.size() && h - b[ptr] >= i){
            ptr ++;
        }
        c[i] += b.size() - ptr;
        // cout << b.size() - ptr << " ";
    }
    // cout << "\n";
    int ans = 1e9;
    int ans2 = 0;
    for(int i = 1; i <= h; i++){
        if(c[i] < ans){
            ans = c[i];
            ans2 = 0;
        }
        if(c[i] == ans) {
            ans2 ++;
        }
    }
    cout << ans << " " << ans2 << "\n";
    
    return 0;
}
