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
// typedef __int128 lll;
// typedef __float128 lld;

//Codeforces - 1202E

//using lower_bound on a sorted list is faster than looking through a map. 

//instead of going through each matching of strings in s, we can instead see for each index in t, how many strings in
//s start and end there, and take the product. 

//to find the count of strings that start and end quickly, we can use string hashing, and the fact that there
//can be at most sqrt(n) unique lengths of strings in s to get an O(n * sqrt(n) * log(n)) solution. Extra log(n) factor
//is for doing hash lookups. 
    
ll mod = 1e9 + 7, pr = 26777;
    
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    string t;
    cin >> t;
    int n;
    cin >> n;
    vector<string> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    sort(a.begin(), a.end(), [](string& a, string& b) -> bool{
        return a.size() < b.size();
    });
    vector<ll> sh(t.size() + 1 + 1, 0), ppow(t.size() + 1, 1);
    for(int i = 1; i <= t.size(); i++){
        sh[i] = (sh[i - 1] * pr + (t[i - 1] - 'a')) % mod;
        ppow[i] = (ppow[i - 1] * pr) % mod;
    }
    vl bcnt(t.size() + 1, 0), ecnt(t.size() + 1, 0);
    for(int i = 0; i < n;){
        map<ll, int> m;
        int ptr = i;
        while(ptr != n && a[i].size() == a[ptr].size()) {
            ll hash = 0;
            for(int j = 0; j < a[ptr].size(); j++){
                hash = (hash * pr + (a[ptr][j] - 'a')) % mod;
            }
            m[hash] ++;
            ptr ++;
        }
        vl h; vi f;
        for(auto j = m.begin(); j != m.end(); j++){
            h.push_back(j->first);
            f.push_back(j->second);
        }
        int len = a[i].size();
        for(int j = 0; j + len <= t.size(); j++){
            ll hash = sh[j + len];
            hash -= (sh[j] * ppow[len]) % mod;
            if(hash < 0){
                hash += mod;
            }
            int ind = lower_bound(h.begin(), h.end(), hash) - h.begin();
            if(ind < h.size() && h[ind] == hash) {
                bcnt[j] += f[ind];
                ecnt[j + len] += f[ind];
            }
        }
        i = ptr;
    }
    ll ans = 0;
    for(int i = 0; i < t.size(); i++){
        ans += bcnt[i] * ecnt[i];
    }
    cout << ans << "\n";
    
    return 0;
}