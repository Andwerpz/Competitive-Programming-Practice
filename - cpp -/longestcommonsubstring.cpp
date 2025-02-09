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

//ICPC NAC 2021 - H

//we can binary search for the substring size, use hashing to speed up comparison. 
//since the bounds are so small, we don't even have to use hashing. 

mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
static const ll M = 1e9 + 9;
const ll B = uniform_int_distribution<ll>(0, M - 1)(rng);
struct hstring {
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

bool is_valid(vector<hstring>& a, vi& sz, int val){
    // cout << "TEST : " << val << endl;
    set<ll> s;
    for(int i = 0; i + val <= sz[0]; i++){
        // cout << "I : " << endl;
        s.insert(a[0].get_hash(i, i + val));
    }
    for(int i = 1; i < a.size(); i++){
        // cout << "I : " << i << endl;
        set<ll> ns;
        for(int j = 0; j + val <= sz[i]; j++) {
            ll h = a[i].get_hash(j, j + val);
            if(s.count(h)) ns.insert(h);
        }
        s = ns;
    }
    return s.size() != 0;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<hstring> a;
    vi sz;
    int low = 1, high = 100;
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        a.push_back(hstring(s));
        sz.push_back(s.size());
        high = min(high, (int) s.size());
    }
    int ans = 0;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(is_valid(a, sz, mid)) low = mid + 1, ans = mid;
        else high = mid - 1;
    }
    cout << ans << "\n";
    
    return 0;
}