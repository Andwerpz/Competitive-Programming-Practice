#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 879A

//implementation

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    int time = 0;
    for(int i = 0; i < n; i++){
        int s, d;
        cin >> s >> d;
        if(time <= s){
            time = s + 1;
            continue;
        }
        int tmp = time - s;
        int mul = (tmp / d) + (tmp % d == 0? 0 : 1);
        time = s + d * mul + 1;
    }
    cout << time - 1 << "\n";
    
    return 0;
}
