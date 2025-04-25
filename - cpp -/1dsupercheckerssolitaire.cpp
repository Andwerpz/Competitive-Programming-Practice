#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl; 
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
// typedef __int128 lll;
// typedef __float128 lld;

//Rutgers University Programming Contest Spring 2025 - E

//just some casework. 

//first, if n is odd, it's impossible to partition n such that the xor sum is 0. 
//if n is 2, then it's always possible.
//otherwise, we have some cases:

// - n is not a multiple of 4
//we always need to have a group of 1 to trigger the computer move. Then, the remaining n - 1 black tokens can be
//partitioned into two groups: n - 1 = e + (e + 1), where e is even. Then, 1 ^ e ^ (e + 1) = 0. We just need to 
//make sure that the first group, excluding the trigger token, is of size <= (e + 1)

// - n is a multiple of 4
//we can't partition n - 1 into e and (e + 1). Instead, we can partition it into (n - 1) = e + e + 1, where e is
//even. Then, we just have to check if the tokens can be moved into position. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vi x(n);
        for(int i = 0; i < n; i++) cin >> x[i];
        if(n == 2) {
            cout << "YES\n";
            continue;
        }
        if(n % 2) {
            cout << "NO\n";
            continue;
        }
        sort(x.begin(), x.end());
        if(n % 4 != 0){
            if(x[0] >= 2) {
                cout << "YES\n";
                continue;
            }
            //x[0] = 1
            int cnt = 0;
            for(int i = 1; i < n; i++) {
                if(x[i] != x[i - 1] + 1) break;
                cnt ++;
            }
            if(cnt > n / 2) cout << "NO\n";
            else cout << "YES\n";
        }
        else {
            //n % 4 == 0
            bool is_valid = true;
            // int gcnt = x[0] - 1;
            // for(int i = 1; i < n; i++){
            //     gcnt += x[i] - x[i - 1] - 1;
            //     if(gcnt < i - 1) is_valid = false;
            // }
            int h = (n - 2) / 2;
            int cnt = 0;
            int tgt = 2;
            for(int i = 1; i < n; i++){
                if(x[i] < tgt) is_valid = false;
                tgt ++;
                cnt ++;
                if(cnt == h) {
                    cnt = 0, tgt ++;
                }
            }
            cout << (is_valid? "YES" : "NO") << "\n";
        }
    }
    
    return 0;
}