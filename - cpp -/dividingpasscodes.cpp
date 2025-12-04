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

//Meta Hacker Cup 2025 Round 1 - D

//this sol too slow, works in O(2^k * k)

//want to count the number of 'strong' passwords
//observe that any password that has > k digits is automatically weak. 
//we can do digit dp on the first k digits. 

const ll mod = 998244353;

int rotl(int x, int s, int n) {
    assert(s >= 0);
    s %= n;
    return ((x << s) | (x >> (n - s))) & ((1 << n) - 1);
}

int k;
const int MAXK = 25;

//mod bitset
//ind
//tight?
ll dp[2][(1 << MAXK)][2];
ll solve(string& s) {
    for(int i = 0; i < (1 << k); i++) {
        dp[0][i][0] = 0;
        dp[0][i][1] = 0;
    }
    for(int ind = min((int) s.size(), k); ind > 0; ind--) {
        cout << "IND : " << ind << endl;
        for(int bits = 0; bits < (1 << k); bits++) {
            dp[1][bits][0] = 0;
            dp[1][bits][1] = 0;
        }
        dp[0][0][ind == s.size()] += 1;
        for(int bits = 0; bits < (1 << k); bits += 2) {
            {
                int dig = s[s.size() - ind] - '0';
                for(int i = 1; i <= dig; i++) {
                    int nmodb = rotl(bits, i, k) | (1 << (i % k));
                    if(nmodb & 1) continue;
                    dp[1][nmodb][i == dig] += dp[0][bits][1];
                    if(dp[1][nmodb][i == dig] >= mod) dp[1][nmodb][i == dig] -= mod;
                }
            }
            {   
                for(int i = 1; i < 10; i++) {
                    int nmodb = rotl(bits, i, k) | (1 << (i % k));
                    if(nmodb & 1) continue;
                    dp[1][nmodb][0] += dp[0][bits][0];
                    if(dp[1][nmodb][0] >= mod) dp[1][nmodb][0] -= mod;
                }
            }
        }
        swap(dp[0], dp[1]);
    }
    ll ans = 0;
    for(int i = 0; i < (1 << k); i++) {
        ans += dp[0][i][0] + dp[0][i][1];
        ans %= mod;
    }
    return ans;
}       

//returns x - 1;
string dec(string x) {
    assert(x != "0");
    for(int i = x.size() - 1; i >= 0; i--) {
        if(x[i] == '0') x[i] = '9';
        else {
            x[i] --;
            break;
        }
    }
    if(x == "0") return x;
    if(x[0] == '0') {
        assert(x.size() > 1);
        return x.substr(1);
    }
    return x;
}

//returns (r - l) % mod;
ll diff(string l, string r) {
    ll ans = 0;
    ll p10 = 1;
    for(int i = r.size() - 1; i >= 0; i--) {
        ans = (ans + (r[i] - '0') * p10) % mod;
        p10 = (p10 * 10) % mod;
    }
    p10 = 1;
    for(int i = l.size() - 1; i >= 0; i--) {
        ans = ans - ((l[i] - '0') * p10) % mod;
        if(ans < 0) ans += mod;
        p10 = (p10 * 10) % mod;
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    ifstream in("dividing_passcodes_input.txt");
    streambuf *cinbuf = cin.rdbuf(); //save old buf
    cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
    
    ofstream out("--out--.txt");
    // streambuf *coutbuf = cout.rdbuf(); //save old buf
    // cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
    
    int t;
    cin >> t;
    int casi = 0;
    while(t--) {
        casi ++;
        string l, r;
        cin >> l >> r >> k;
        l = dec(l);
        ll ans = diff(l, r);
        ans -= solve(r);
        ans += solve(l);
        while(ans < 0) ans += mod;
        ans %= mod;
        out << "Case #" << casi << ": " << ans << "\n";
        cout << "DONE WITH : " << casi << " " << ans << endl;
    }
    
    return 0;
}