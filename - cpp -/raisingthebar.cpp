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

//Calgary 2022 - J

//can just simulate long division until you find a cycle. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, d;
    cin >> n >> d;
    int pow10 = 0;
    int ptr = 1;
    while(ptr < d) {
        ptr *= 10;
        pow10 ++;
    }
    vi a(0);
    vector<int> v(ptr, -1);
    ptr = n;
    v[ptr] = 0;
    int cnt = 1;
    int fans, ians;
    while(true) {
        ptr *= 10;
        int cur = ptr / d;
        ptr %= d;
        // cout << "PTR : " << cur << " " << ptr << endl;
        if(v[ptr] != -1){
            fans = v[ptr];
            ians = cnt - v[ptr];
            if(ptr == 0){
                ians = 0;
            }
            break;
        }
        v[ptr] = cnt;
        cnt ++;
        a.push_back(cur);
    }
    cout << fans << " " << ians << "\n";
    
    return 0;
}