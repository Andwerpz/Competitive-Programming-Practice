#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<ll> vl;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

//ICPC NAC 2023 - L

//Observe that if all the numbers are odd, then the first person to go always loses. This is because
//the first person has to make at least one even pile, then the second person can always turn 
//any even piles the first person makes into odd ones. Note that when all the piles only have 1
//stone, the first person loses. 

//When can the first person avoid this? Observe that if there exists some even piles, they can
//always (not quite) turn all the even piles into odd piles. The only exception is when there are
//only even piles and n % 2 = 1. 

//So now, assume that there are only even piles and n % 2 = 1. Observe that the first person to
//make an odd pile loses, so we can divide every value by 2 and not affect the game. Actually, this
//is identical to the original game. So apply the same logic recursively until you find a winner. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vl a(n);
        for(int i = 0; i < n; i++) cin >> a[i];
        int _ecnt = 0;
        for(int i = 0; i < n; i++) _ecnt += (a[i] % 2 == 0);
        if(n % 2 == 0){
            cout << (_ecnt != 0? 1 : 0) << "\n";
            continue;
        }
        int ans = -1;
        while(true) {
            int ecnt = 0;
            for(int i = 0; i < n; i++) ecnt += (a[i] % 2 == 0);
            if(ecnt == 0) {
                ans = 0;    //Alice loses
                break;
            }
            if(ecnt != n) {
                ans = 1;    //alice wins
                break;
            }
            for(int i = 0; i < n; i++) a[i] /= 2;
        }
        cout << ans << "\n";
    }

    return 0;
}