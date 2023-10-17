#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Kattis - overdraft

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    int sum = 0;
    int ans = 0;
    for(int i = 0; i < t; i++){
        int a;
        cin >> a;
        sum += a;
        ans = max(ans, -sum);
    }
    cout << ans << "\n";
    
    return 0;
}
