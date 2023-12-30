#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//AtCoder - ARC131C

//if you can't win on the first move, then it's impossible to force a win on any move except for the 
//move where you eat the last cookie. 

//don't ask me why this works. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> bits(31, 0);
    int sum = 0;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        for(int j = 0; j < 31; j++){
            bits[j] += (a[i] >> j) & 1;
        }
        sum ^= a[i];
    }
    bool instawin = false;
    for(int i = 0; i < n; i++){
        if(a[i] == sum) {
            instawin = true;
            break;
        }
    }
    if(instawin) {
        cout << "Win\n";
        return 0;
    }
    cout << (n % 2 == 1? "Win\n" : "Lose\n");
    
    return 0;
}
