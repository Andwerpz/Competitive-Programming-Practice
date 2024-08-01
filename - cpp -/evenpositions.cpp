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

//Codeforces - 1997C

//if we think of '(' as +1 and ')' as -1, then the cost of a bracket sequence is simply the sum of all prefix sums
//of that bracket sequence. Also, any valid bracket sequence must have all non negative prefix sums, and the sum of 
//the entire array must be 0. 

//since we are trying to minimize the cost anyways, we can just greedily minimize the prefix sum every time we
//need to choose the next bracket in the sequence. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        string s;
        cin >> s;
        ll ans = 0;
        ll sum = 0;
        for(int i = 0; i < n; i++){
            if(i % 2 == 0){
                if(sum == 0){
                    sum ++;
                }
                else {
                    sum --;
                }
            }
            else {
                sum += s[i] == '('? 1 : -1;
            }
            ans += sum;
        }
        cout << ans << "\n";
    }
    
    return 0;
}