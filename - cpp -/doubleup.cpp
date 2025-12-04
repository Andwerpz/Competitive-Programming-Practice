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
typedef __int128 lll;
// typedef __float128 lld;

//ECNA 2023 - F

//to find the greatest value we can make, we can use a monotonic stack
//note that values can be relatively large, just use 128 bit int

lll read_lll() {
    string s;
    cin >> s;
    lll ans = 0;
    for(int i = 0; i < s.size(); i++) {
        ans = (ans * 10) + (s[i] - '0');
    }
    return ans;
}

void out_lll(lll x) {
    if(x == 0) {
        cout << "0";
        return;
    }
    string s;
    while(x != 0) {
        int d = x % 10;
        x /= 10;
        // cout << "D : " << d << " " << (ll) x << "\n";
        s.push_back('0' + d);
    }
    reverse(s.begin(), s.end());
    cout << s;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<lll> a(n);
    for(int i = 0; i < n; i++) a[i] = read_lll();
    lll ans = 0;
    stack<lll> s;
    for(int i = 0; i < n; i++) {
        while(s.size() != 0 && s.top() <= a[i]) {
            if(s.top() == a[i]) a[i] += s.top();
            s.pop();
        }
        s.push(a[i]);
    }
    while(s.size() != 0) {
        // out_lll(s.top());
        ans = max(ans, s.top());
        s.pop();
    }
    out_lll(ans);
    
    return 0;
}