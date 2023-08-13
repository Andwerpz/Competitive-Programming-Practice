#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1856B

//we can construct 'b' by starting with 'a'.
//for each element that is above 1, we can just subtract 1 from it, and add it somewhere else. 

//the problem is that we have to add 1 to elements that are originally equal to 1, so if the
//amount of 1s exceeds the amount of extra value we have, then it is impossible. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<ll> a(n);
        ll extra = 0;
        ll onecnt = 0;
        for(int i = 0; i < n; i++){
            cin >> a[i];
            extra += a[i] - 1;
            if(a[i] == 1){
                onecnt ++;
            }
        }
        if(extra < onecnt || n == 1) {
            cout << "NO\n";
        }
        else {
            cout << "YES\n";
        }
    }
    
    return 0;
}
