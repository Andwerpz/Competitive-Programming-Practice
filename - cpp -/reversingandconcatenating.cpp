#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef array<int, 2> pii;
typedef array<ll, 2> pll;
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

//AtCoder - AGC37E

//given sufficiently large k, we can just make the entire string the smallest character. So we're going to at
//most do around 15 or so operations, which means we can pretty much simulate it. 

//For every operation before the last one, we're going to want to select the lexicographically minimum string when 
//reversed. We can just do a complete search every time. 

string apply_op(string s) {
    string tmp = s;
    reverse(tmp.begin(), tmp.end());
    return s + tmp;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    k = min(k, 15);
    for(int i = 0; i < k - 1; i++){
        string tmp = apply_op(s);
        string ns = s.substr(0, n);
        reverse(ns.begin(), ns.end());
        for(int i = 1; i + n <= 2 * n; i++){
            string nxt = tmp.substr(i, n);
            reverse(nxt.begin(), nxt.end());
            if(nxt < ns) ns = nxt; 
        }
        reverse(ns.begin(), ns.end());
        s = ns;
    }
    string ans = "";
    {
        string tmp = apply_op(s);
        ans = s.substr(0, n);
        for(int i = 1; i + n <= 2 * n; i++){
            string nxt = tmp.substr(i, n);
            reverse(nxt.begin(), nxt.end());
            if(nxt < ans) ans = nxt; 
        }
    }
    cout << ans << "\n";
    
    return 0;
}