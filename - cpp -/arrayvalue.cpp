#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef std::pair<int, int> pii;
typedef std::pair<ll, ll> pll;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1983F

//if we can count the number of subarrays having value less than or equal to some value x in n * log(n) time, 
//then we can simply binary search for the minimum x where the number of subarrays with value
//less than or equal to x is >= k, and that x is our answer. 

//To find the number of subarrays with value less than or equal to x, we can use a 2 pointer method, 
//and a trie. The trie should support adding, removing, and querying the minimum xor value against any value
//inside the trie. All these operations can be done in log(n) time. 

//as for the 2 pointer, notice that if some array has value v, then any subarray of that array must have
//value greater than or equal to v. This means that for our two pointer, we can just find for each l, 
//the maximum r in which the segment [l, r) has value > x, and then take the complement. 

static const int N = (1e5 + 100) * 30;
int trie_c[N][2], trie_subt[N];
struct TrieXOR {
    int nc = 1;

    TrieXOR() {
        clear();
    }

    void clear() {
        nc = 1;
        trie_c[0][0] = -1, trie_c[0][1] = -1;
        trie_subt[0] = 0;
    }

    int size() {
        return trie_subt[0];
    }

    void insert(int x) {
        int ptr = 0;
        trie_subt[0] ++;
        for(int i = 29; i >= 0; i--){   
            bool bit = x & (1 << i);
            if(trie_c[ptr][bit] == -1){
                trie_subt[nc] = 0;
                trie_c[nc][0] = -1, trie_c[nc][1] = -1;
                trie_c[ptr][bit] = nc;
                nc ++;
            }
            ptr = trie_c[ptr][bit], trie_subt[ptr] ++;
        }
    }

    int count(int x) {
        int ptr = 0;
        for(int i = 29; i >= 0; i--){
            bool bit = x & (1 << i);
            if(trie_c[ptr][bit] == -1)
                return 0;
            ptr = trie_c[ptr][bit];
        }
        return trie_subt[ptr];
    }

    void erase(int x) {
        if(count(x) == 0)
            return;
        int ptr = 0;
        trie_subt[0] --;
        for(int i = 29; i >= 0; i--){
            bool bit = x & (1 << i);
            ptr = trie_c[ptr][bit], trie_subt[ptr] --;
        }
    }

    int query_max(int x) {
        if(size() == 0)
            return -1;
        int ans = 0, ptr = 0;
        for(int i = 29; i >= 0; i--){
            bool bit = x & (1 << i);
            if(trie_c[ptr][!bit] != -1 && trie_subt[trie_c[ptr][!bit]] != 0)
                ans += (1 << i), ptr = trie_c[ptr][!bit];
            else 
                ptr = trie_c[ptr][bit];
        }
        return ans;
    }

    int query_min(int x) {
        if(size() == 0)
            return -1;
        int ans = 0, ptr = 0;
        for(int i = 29; i >= 0; i--){
            bool bit = x & (1 << i);
            if(trie_c[ptr][bit] != -1 && trie_subt[trie_c[ptr][bit]] != 0)
                ptr = trie_c[ptr][bit];
            else
                ans += (1 << i), ptr = trie_c[ptr][!bit];
        }
        return ans;
    }
};

ll get_amt(ll n, vector<int>& a, int val, TrieXOR& trie) {
    trie.clear();
    ll ans = n * (n - 1) / 2;
    int r = 0;
    for(int i = 0; i < n; i++){
        while(r != n) {
            if(r != i && trie.query_min(a[r]) <= val){
                break;
            }
            trie.insert(a[r]);
            r ++;
        }
        ans -= r - i - 1;
        trie.erase(a[i]);
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    TrieXOR trie;
    vector<int> a(1e5 + 1);
    int t;
    cin >> t;
    while(t--){
        ll n, k;
        cin >> n >> k;
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        int low = 0;
        int high = (1 << 30) - 1;
        int ans = high;
        while(low <= high) {
            int mid = low + (high - low) / 2;
            if(get_amt(n, a, mid, trie) >= k){
                ans = min(ans, mid);
                high = mid - 1;
            }
            else {
                low = mid + 1;
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}