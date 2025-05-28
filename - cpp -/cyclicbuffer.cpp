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

//2021 ICPC Asia Macau Regional Contest - G

//observe that if the next needed element is outside of the input buffer, we can either rotate the array to the left
//or to the right to make it be inside. Notice that we should only rotate the minimum amount to get the next element
//inside, before considering the next element, so the element will either end up on the left or right edge of the buffer. 

//The other case is when the next element is already inside the buffer, so it may not be on the left or right edge. 

//we can define a dp, dp[i][j] = min shifts where
// - visited first i elements
// - last visited is at end of buffer? = j
//since this doesn't make sense for elements that are already within the previous buffer, for each [i][j], we need to 
//precompute the next element that is outside of the current buffer position, or say that there isn't any. 

//you can do this with a set, but that TLE. Use a segment tree to not TLE. The time constraints are quite tight. 

struct Segtree {
    //note that t[0] is not used
    typedef int T;    
    int n;
    T* t;
    T uneut, qneut;

    Segtree() {}
    Segtree(int n, T updateNeutral, T queryNeutral) {
        this->n = n;
        t = new T[2 * n];
        uneut = updateNeutral;
        qneut = queryNeutral;
        for(int i = 0; i < n; i++) t[i + n] = uneut;
        build();
    }

    void assign(vector<T>& arr) {
        for(int i = 0; i < min(n, (int) arr.size()); i++)
            t[i + n] = arr[i];
        build();
    }

	// build the tree after manually assigning the values.
    void build() { 
        for (int i = n - 1; i > 0; i--)
            t[i] = min(t[i * 2], t[i * 2 + 1]);
    }

    void modify(int p, T value) { // set value at position p
        p += n;
        t[p] = value;
        for (p /= 2; p > 0; p /= 2)
            t[p] = min(t[p * 2], t[p * 2 + 1]);
    }

    T query(int l, int r) { // sum on interval [l, r)
        T l_res = qneut, r_res = qneut;
        bool l_none = true, r_none = true;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l % 2 == 1) {
                if(l_none) {l_none = false; l_res = t[l];}
                else l_res = min(l_res, t[l]);
                l++;
            }
            if (r % 2 == 1) {
                r--;
                if(r_none) {r_none = false; r_res = t[r];}
                else r_res = min(t[r], r_res);
            }
        }
        if(l_none) return r_res;
        if(r_none) return l_res;
        return min(l_res, r_res);
    }

    T query(int ind) {
        return this->query(ind, ind + 1);
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        vi a(n);
        for(int i = 0; i < n; i++) cin >> a[i];
        for(int i = 0; i < n; i++) a[i] --;
        vi pos(n);
        for(int i = 0; i < n; i++) pos[a[i]] = i;
        //dp[i][j] = min shifts where
        // - visited first i elements
        // - last visited is at end of buffer? = j
        vvl dp(n + 1, vl(2, 1e18)); 
        dp[0][0] = 0;
        vvi nxt(n + 1, vi(2, -1));  //at every visited state and buffer pos, what's the next missing?
        {
            if(k == n) nxt[0][0] = n;
            else {
                nxt[0][0] = n;
                for(int i = k; i < n; i++){
                    nxt[0][0] = min(nxt[0][0], a[i]);
                }
                Segtree segt(n, n, n); 
                for(int i = n - 1; i >= 0; i--){
                    // for(int j = 0; j < n; j++) cout << segt.query(j) << " ";
                    // cout << "\n";
                    //left side
                    {
                        int l = pos[i], r = l + k;
                        r %= n;
                        if(r < l) nxt[i + 1][0] = segt.query(r, l);
                        else nxt[i + 1][0] = min(segt.query(0, l), segt.query(r, n));
                        // cout << "QUERY : " << segt.query(0, l) << " " << i << " " << l << "\n";
                    }
                    //right side
                    {
                        int r = pos[i] + 1, l = r - k;
                        l = (l + n) % n;
                        if(r < l) nxt[i + 1][1] = segt.query(r, l);
                        else nxt[i + 1][1] = min(segt.query(0, l), segt.query(r, n));
                    }
                    //update segt
                    segt.modify(pos[i], i);
                }
            }
            // set<int> s;
            // for(int i = k; i < n; i++) s.insert(a[i]);
            // if(s.size() != 0) nxt[0][0] = *(s.begin());
            // else nxt[0][0] = n;
            // for(int i = 0; i < n; i++){
            //     int f = a[i], l = a[(i + k - 1) % n];
            //     // cout << "FL : " << f << " " << l << "\n";
            //     {
            //         auto ptr = s.lower_bound(f);
            //         if(ptr == s.end()) nxt[f + 1][0] = n;
            //         else nxt[f + 1][0] = *ptr;
            //         // cout << nxt[f + 1][0] << "\n";
            //     }
            //     {
            //         auto ptr = s.lower_bound(l);
            //         if(ptr == s.end()) nxt[l + 1][1] = n;
            //         else nxt[l + 1][1] = *ptr;
            //     }
            //     s.erase(a[(i + k) % n]);
            //     s.insert(f);
            // }
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < 2; j++){
                int bpos;   //left buffer bound
                if(i == 0) bpos = i;
                else if(j == 0) bpos = pos[i - 1];
                else bpos = (pos[i - 1] - k + 1 + n) % n;
                int next = nxt[i][j];
                if(next == -1) continue;
                // cout << "DP : " << i << " " << j << " " << next << " " << dp[i][j] << " " << bpos << "\n";
                if(next == n) {
                    dp[n][0] = min(dp[n][0], dp[i][j]);
                    continue;
                }
                int npos = pos[next];
                //go left
                int ldist = (bpos - npos + n) % n;
                dp[next + 1][0] = min(dp[next + 1][0], dp[i][j] + ldist);
                //go right
                int rdist = (npos - bpos - (k - 1) + n * 2) % n;
                dp[next + 1][1] = min(dp[next + 1][1], dp[i][j] + rdist);
            }
        }
        cout << min(dp[n][0], dp[n][1]) << "\n";
    }
    
    return 0;
}