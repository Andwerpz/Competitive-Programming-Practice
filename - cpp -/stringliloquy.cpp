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

//UTPC Contest 03-22-24 Div. 1 - H

//first note that the number of unique lengths in the distinct words is no more than \sqrt(10^5). For some length, we can 
//find out for every starting point whether or not a word of that length starts there in O(N) using string hashing. 
//then, answering the queries becomes O(\sqrt(10^5)) each by iterating through all the lengths. 

mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
static const ll M = 1e9 + 9;
ll B = uniform_int_distribution<ll>(0, M - 1)(rng);

struct hstring {
	// change M and B if you want

	// pow[i] contains B^i % M
	vector<long long> pow;

	// p_hash[i] is the hash of the first i characters of the given string
	vector<long long> p_hash;

	hstring(const string &s) : p_hash(s.size() + 1), pow(1, 1){
		while (pow.size() <= s.size()) { pow.push_back((pow.back() * B) % M); }
		p_hash[0] = 0;
		for (int i = 0; i < s.size(); i++) {
			p_hash[i + 1] = ((p_hash[i] * B) % M + s[i]) % M;
		}
	}

	long long get_hash(int start, int end) {
		long long raw_val = (p_hash[end] - (p_hash[start] * pow[end - start]));
		return (raw_val % M + M) % M;
	}
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m, q;
    cin >> n >> m >> q;
    string s;
    cin >> s;
    hstring hs(s);
    vector<vector<string>> b(100001);
    vi lens;
    for(int i = 0; i < m; i++) {
        string t;
        cin >> t;
        b[t.size()].push_back(t);
    }
    for(int i = 1; i < b.size(); i++) if(b[i].size() != 0) lens.push_back(i);
    vvl pfx(lens.size(), vl(n + 1, 0));
    for(int i = 0; i < lens.size(); i++){
        int len = lens[i];
        set<ll> h;
        for(string t : b[len]) h.insert(hstring(t).get_hash(0, len));
        for(int j = 0; j + len <= n; j++){
            pfx[i][j + 1] += h.count(hs.get_hash(j, j + len));
        }
        for(int j = 1; j <= n; j++) pfx[i][j] += pfx[i][j - 1];
    }
    while(q--){
        int l, r;
        cin >> l >> r;
        l --;
        ll ans = 0;
        for(int i = 0; i < lens.size(); i++) {
            int len = lens[i];
            if(len > r - l) continue;
            ans += pfx[i][r - (len - 1)] - pfx[i][l];
        }
        cout << ans << "\n";
    }
    
    return 0;
}