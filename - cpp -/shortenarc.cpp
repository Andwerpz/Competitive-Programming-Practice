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

//AtCoder - ARC140B

//Looking at the two operations given, the first one takes an 'R', and removes the 'A' before it
//and 'C' after it. The second one takes an 'ARC' and just removes the 'R'. 

//The first observation we can make is that performing an operation will not affect operations 
//on any other location, just the location where we performed the operation. This is convenient
//because we can then consider every occurrence of 'R' seperately. 

//Second, the only relevant thing for an occurrence of 'R' is the amount of 'A's preceding and 'C's
//succeeding, specifically the minimum of the two. It's important because it dictates how many 
//type 1 operations we can do, and whether or not we can do a type 2 operation. 

//As for the strategy, we'll want to apply type 1 operations on 'R's with the most 'A' and 'C's, and
//type 2 operations on the 'R's with the least amount of 'A' and 'C's. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    string s;
    cin >> s;
    map<int, int> f;
    for(int i = 0; i < n; i++){
        if(s[i] != 'R') continue;
        int cnt = 0;
        while(true) {
            if(i - 1 - cnt < 0 || i + 1 + cnt >= n) break;
            if(s[i - 1 - cnt] != 'A' || s[i + 1 + cnt] != 'C') break;
            cnt ++;
        }
        if(cnt != 0){
            f[cnt] ++;
        }
    }
    int ans = 0;
    while(f.size() != 0) {
        if(ans % 2 == 0){
            int next = f.rbegin()->first;
            f[next] --;
            if(f[next] == 0) f.erase(next);
            if(next != 1) f[next - 1] ++;
        }
        else {
            int next = f.begin()->first;
            f[next] --;
            if(f[next] == 0) f.erase(next);
        }
        ans ++;
    }
    cout << ans << "\n";
    
    return 0;
}