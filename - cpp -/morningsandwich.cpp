#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1849A

//let's reserve one piece of bread to be the bottom/top piece. 

//then, the rest of the layers must alternate between bread and cheese/ham.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int b, c, h;
        cin >> b >> c >> h;
        int l = c + h;
        b --;
        int ans = min(b, l) * 2;
        ans ++;
        cout << ans << "\n";
    }
    
    return 0;
}
