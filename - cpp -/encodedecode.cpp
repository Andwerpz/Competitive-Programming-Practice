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

//Codeforces - 2168 A1 A2

//first 'communication' problem!

//observe that when n = 10^4, we have a lil less than 10 characters to encode each number, which may be up
//to 10^9. 

//with base-26 encoding, we can encode each number within 7 characters, which gives plenty of leeway. 

string encode(int x) {
    string ret = "";
    for(int i = 0; i < 7; i++) {
        char c = 'a' + (x % 26);
        x /= 26;
        ret.push_back(c);
    }
    return ret;
}

int decode(string s) {
    int ret = 0;
    for(int i = 0; i < 7; i++) {
        int dig = *(s.rbegin()) - 'a';
        s.pop_back();
        ret = (ret * 26) + dig;
    }
    return ret;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    string run;
    cin >> run;
    if(run == "first") {
        int n;
        cin >> n;
        vi a(n);
        for(int i = 0; i < n; i++) cin >> a[i];
        string ans = encode(n);
        for(int i = 0; i < n; i++) ans += encode(a[i]);
        cout << ans << "\n";
    }
    else {
        string s;
        cin >> s;
        assert(s.size() % 7 == 0);
        int n = decode(s.substr(0, 7));
        assert(s.size() / 7 == n + 1);
        vi a(n);
        for(int i = 0; i < n; i++) {
            a[i] = decode(s.substr((i + 1) * 7, 7));
        }
        cout << n << "\n";
        for(int x : a) cout << x << " ";
        cout << "\n";
    }
    
    return 0;
}