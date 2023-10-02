#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1180A

//implementation. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    int ans = 0;
    for(int i = 1; i <= n; i++){
        if(i == 1){
            ans += 1;
        }
        else {
            ans += (i - 1) * 4;
        }
    }
    cout << ans << "\n";
    
    return 0;
}
