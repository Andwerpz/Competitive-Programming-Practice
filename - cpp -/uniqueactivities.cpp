#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

typedef pair<int,int> pii;
typedef vector<int> vi;
#define rep(i, a ,b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define z(s) (int) (x).size()

mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

//SWERC 2020 - K

struct hstring {
    static const ll M = 1e9 + 9;
    ll B = uniform_int_distribution<ll>(0, M - 1)(rng);
    vector<long long> pow;
    vector<long long> p_hash;
    hstring(const string &s) : p_hash(s.size() + 1) , pow(1, 1) {
        while(pow.size() <= s.size()) {
            pow.push_back((pow.back() * B) % M);
        }
        for(int i = 0; i < s.size(); i++) {
            p_hash[i + 1] = ((p_hash[i] * B) % M + s[i]) % M;
        }
    }
    long long get_hash(int start, int end) {
        long long raw_val = (p_hash[end] - (p_hash[start] * pow[end - start]));
        return (raw_val % M + M) % M;
    }
};

struct hstring1 {
    static const ll M = 1e9 + 7;
    ll B = uniform_int_distribution<ll>(0, M - 1)(rng);
    vector<long long> pow;
    vector<long long> p_hash;
    hstring1(const string &s) : p_hash(s.size() + 1) , pow(1, 1) {
        while(pow.size() <= s.size()) {
            pow.push_back((pow.back() * B) % M);
        }
        for(int i = 0; i < s.size(); i++) {
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
    cin.tie(0), cout.tie(0);

    string s; cin >> s;
    hstring h(s);
    hstring1 h1(s);
    int n = s.size();
    int l = 1, r = n;
    int last = -1;

    auto get_idx = [&](int m) -> int {
        map<array<int,2>, int> mp;
        vector<pair<array<int,2>, int>> hs;
        for(int l = 0; l + m <= n; l++) {
            ll aa = h.get_hash(l, l + m);
            ll bb = h1.get_hash(l, l + m);
            array<int,2> a = {aa, bb};
            hs.push_back({a, l});
            // mp[a]++;
        }

        sort(hs.begin(), hs.end());
        int f = INT_MAX;

        for(int i = 0; i < hs.size(); i++) {
            int ok = 1;
            if(i && hs[i].first == hs[i - 1].first) ok = 0;
            if(i + 1 < hs.size() && hs[i].first == hs[i + 1].first) ok = 0;
            if(ok) f = min(f, hs[i].second);
        }
        return f;
    };

    while(l != r) {
        int m = (l + r) / 2;
        int f = get_idx(m);
        if(f == INT_MAX) {
            l = m + 1;
        } else {
            r = m;
        }
    }

    cout << s.substr(get_idx(l), l) << '\n';

    return 0;
}
