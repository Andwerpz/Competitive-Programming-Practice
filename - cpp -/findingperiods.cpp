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

//CSES - 1733

//another string hashing + harmonic 

mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
struct hstring {
	// change M and B if you want
	static const ll M = 1e9 + 9;
	ll B = uniform_int_distribution<ll>(0, M - 1)(rng);

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
    
    string s;
    cin >> s;
    hstring h(s);
    int n = s.size();
    for(int i = 1; i <= n; i++){
        bool works = true;
        for(int l = i; l < n; l += i){
            int len = min(i, n - l);
            if(h.get_hash(0, len) != h.get_hash(l, l + len)) {
                works = false;
            }
        }
        if(works){
            cout << i << " ";
        }
    }
    cout << "\n";
    
    return 0;
}