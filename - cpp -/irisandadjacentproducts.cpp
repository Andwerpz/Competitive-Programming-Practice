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

//Codeforces - 2006D

//given some array, how to compute the minimum 2 operations?
//first, let's try to consider the optimal rearrangement. If we sort the elements in ascending order, then we'd always
//want to rearrange the elements like so: a[n - 1] * a[0] * a[n - 2] * a[1] ... and so on. We're kind of pairing
//every large element off with a small element. 

//next, note that any small element has to be <= sqrt(k), and that any large element x can only be handled by small elements 
//up to k / x. So if cnt(l, r) is the count of elements in range [l, r], then the array can be done in 0 type 2 operations 
//if cnt(1, i) >= cnt(floor(k / (i + 1)) + 1, k) is true for all i, 1 <= i <= sqrt(k). 

//we can keep a pfx and sfx array to keep track of the counts for small and large elements, and use Mo's algorithm to 
//update them over all queries efficiently. Answering each query only takes sqrt(k) time. 

//be mindful of the special case where we can leave a trailing large element. 

void add_elem(vi& pfx, vi& sfx, int val, int k, int rk) {
    if(val <= rk) {
        pfx[val] ++;
    }
    else {
        sfx[k / val] ++;
    }
}

void rm_elem(vi& pfx, vi& sfx, int val, int k, int rk) {
    if(val <= rk) {
        pfx[val] --;
    }
    else {
        sfx[k / val] --;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    vi pfx(1e3 + 100, 0), sfx(1e3 + 100, 0);
    int t;
    cin >> t;
    while(t--){
        int n, q, k;
        cin >> n >> q >> k;
        vi a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        vector<pair<pii, int>> queries(q);
        for(int i = 0; i < q; i++){
            cin >> queries[i].first.first >> queries[i].first.second;
            queries[i].first.first --;
            queries[i].second = i;
        }
        int buck_sz = sqrt(n);
        //mo's algorithm. 
        sort(queries.begin(), queries.end(), [&buck_sz](pair<pii, int>& a, pair<pii, int>& b) -> bool{
            int a_buck = a.first.first / buck_sz;
            int b_buck = b.first.first / buck_sz;
            if(a_buck != b_buck) {
                return a_buck < b_buck;
            }
            return (a.first.second < b.first.second);
        });
        queries.push_back({{n, n}, q}); //to clear the array
        vi ans(q);
        int l = 0;
        int r = 0;
        int rk = sqrt(k);
        for(int i = 0; i <= q; i++){
            int nl = queries[i].first.first;
            int nr = queries[i].first.second;
            int qind = queries[i].second;
            while(nl < l) {
                add_elem(pfx, sfx, a[l - 1], k, rk);
                l --;
            }
            while(nr > r){
                add_elem(pfx, sfx, a[r], k, rk);
                r ++;
            }
            while(nl > l){
                rm_elem(pfx, sfx, a[l], k, rk);
                l ++;
            }
            while(nr < r){
                rm_elem(pfx, sfx, a[r - 1], k, rk);
                r --;
            }
            if(i == q){
                break;
            }
            int cans = 0;
            int scnt = 0, bcnt = 0;
            for(int j = 1; j <= rk; j++){
                scnt += pfx[j];
                bcnt += sfx[j];
                if(bcnt > scnt) {
                    int diff = bcnt - scnt;
                    if(scnt + bcnt == r - l){   //when we've gotten all elements, last element can be big. 
                        diff = diff / 2;
                    }
                    else {  //general case, we want last element to be small
                        diff = (diff + 1) / 2;
                    }
                    cans += diff;
                    bcnt -= diff;
                    scnt += diff;
                }
            }
            ans[qind] = cans;
        }
        for(int i = 0; i < q; i++){
            cout << ans[i] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}