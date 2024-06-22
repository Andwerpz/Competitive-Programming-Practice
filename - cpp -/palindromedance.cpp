#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1040A

//the only way some setup is invalid is if two dancers have already bought mismatched suits. 

//otherwise, for each dancer look at the dancer it needs to match with and buy their suit. If the other person also
//doesn't have a suit, buy the cheaper one. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, a, b;
    cin >> n >> a >> b;
    int ans = 0;
    vector<int> l(n);
    for(int i = 0; i < n; i++) {
        cin >> l[i];
    }
    for(int i = 0; i < n / 2; i++){
        int x = l[i];
        int y = l[n - i - 1];
        if(x != 2 && y != 2) {
            if(x != y){
                cout << "-1\n";
                return 0;
            }
            continue;
        }
        if(x == 0 || y == 0){
            ans += a;
        }
        else if(x == 1 || y == 1){
            ans += b;
        }
        else {
            ans += 2 * min(a, b);
        }
    }
    if(n % 2 == 1 && l[n / 2] == 2){
        ans += min(a, b);
    }
    cout << ans << "\n";
    
    return 0;
}