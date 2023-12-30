#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1909A

//for each location, just check which buttons you need to reach it from the origin. 
//if all 4 buttons are needed, print NO. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        bool u = false;
        bool d = false;
        bool l = false;
        bool r = false;
        for(int i = 0; i < n; i++){
            int x, y;
            cin >> x >> y;
            if(x < 0){
                l = true;
            }
            if(x > 0){
                r = true;
            }
            if(y < 0){
                d = true;
            }
            if(y > 0){
                u = true;
            }
        }
        int sum = u + d + l + r;
        cout << (sum == 4? "No" : "Yes") << "\n";
    }
    
    return 0;
}
