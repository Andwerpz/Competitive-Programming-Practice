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

//AtCoder - ARC78E

//Let's first determine the length of the number. If we query 10^p and 10^(p + 1) - 1, then
//they'll both return true if p + 1 is the length of N. Actually, there are two exceptions: 
//if is of form 10^d, then this test will return true for all p >= d, and if N is of form
//10^d - 1, then it'll return true for all p <= d. To tell the two apart, we can take advantage
//of the fact that N has a maximum length and query p = 10. If that is true, then we know N
//is of form 10^d, and can take the minimum valid p, otherwise take the maximum. 

//Once we know the length, finding N is pretty easy. We can fix n to be greater than N, and 
//just use the lexicographical ordering to binary search. To ensure n is greater than N, just pad
//the end of n with a bunch of 0s. 

//Finding the length takes around 20 queries, and binary search around 30, so it sits comfortably
//below the limit. 

int N;
bool query(ll n) {
    cout << "? " << n << endl;
    string s;
    cin >> s;
    return s == "Y";
    // return (n <= N && to_string(n) <= to_string(N)) || (n > N && to_string(n) > to_string(N));
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    // cin >> N;
    //determine length
    int mn_len = 1e9, mx_len = -1e9;
    int len = -1;
    for(int i = 1; i < 11; i++){
        ll tmp = 1;
        for(int j = 0; j < i - 1; j++){
            tmp *= 10;
        }
        if(query(tmp) && query(tmp * 10 - 1)) {
            mn_len = min(mn_len, i), mx_len = max(mx_len, i);
        }
    }
    len = mx_len == 10? mn_len : mx_len;
    //binary search
    ll low = 1;
    for(int i = 0; i < len - 1; i++) low *= 10;
    ll high = low * 10 - 1;
    ll ans = high;
    while(low <= high){
        ll mid = low + (high - low) / 2;
        ll tmp = mid;
        while(tmp < 1e11) tmp *= 10;
        if(!query(tmp)) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
            ans = mid;
        }
    }
    cout << "! " << ans << endl;
    
    return 0;
}