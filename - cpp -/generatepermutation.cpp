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

//Codeforces - 2001B

//from the perspective of the left typewriter, a carriage return happens when we have to go from 
//some index i to j where i > j. It's the opposite for the right typewriter. So we want to make it such that
//the number of i > j and i < j are equal. 

//we can do this easily by placing the first number at the left end, second at right end, third at left end, and
//so on. We can also see that if n is even, then it's impossible due to there being an odd amount of 'transitions'. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        if(n % 2 == 0){
            cout << "-1\n";
            continue;
        }
        vi ans(n);
        int ptr = 1;
        int l = 0;
        int r = n - 1;
        for(int i = 0; i < n / 2; i++){
            ans[l++] = ptr ++;
            ans[r--] = ptr ++;
        }
        ans[l] = ptr;
        for(int i = 0; i < n; i++){
            cout << ans[i] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}