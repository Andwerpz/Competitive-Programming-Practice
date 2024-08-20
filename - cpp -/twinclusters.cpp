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

//Codeforces - 1835C

//double use of pidgeonhole principle D:

//first observe that if you can find any two segments such that the xor sum is the same, (doesn't matter if they're intersecting, 
//their beginnings and ends just have to be different) then we've found our answer. If they are intersecting, then we can simply
//subtract the intersecting part from both segments and they'll still be the same sum. 

//How many such segments exist? Since there are 2^(k + 1) elements, there are around 2^(2k + 1) subarrays which is around 4^k * 2. 
//As there are only 4^k unique values for XOR, there must be a duplicate according to pidgeonhole principle. 

//How do we find such a duplicate? First, replace A with the prefix array of A, P. Note that the sum over a subarray is equal to 
//the sum of the prefix sums of the left and right bounds. Next, consider the first k bits of each element in P. Since there are
//2 * 2^k + 1 elements (including the 0 prefix sum), and only 2^k unique values of the first k bits, it's guaranteed that we will find
//at least 2^k + 1 prefix sums that have appeared before. 

//Then, we see if two duplicate pairs share the same last k bits. Once again, since there are 2^k + 1 pairs, and only 2^k values of
//the last k bits, it's guaranteed that we'll find at least 1 duplicate. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int t;
    cin >> t;
    while(t--){
        int k;
        cin >> k;
        int n = (1 << (k + 1));
        vl a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        vi p((1 << k), -1);
        vector<pii> p2((1 << k), {-1, -1});
        p[0] = 0;
        vl pfx(n + 1, 0);
        int l1, r1, l2, r2;
        for(int i = 1; i <= n; i++){
            pfx[i] = pfx[i - 1] ^ a[i - 1];
            ll m1 = pfx[i] & ((1 << k) - 1);
            if(p[m1] != -1){
                int cl = p[m1];
                int cr = i;
                ll m2 = (pfx[cr] ^ pfx[cl]) >> k;
                if(p2[m2].first != -1){
                    l1 = cl;
                    r1 = cr;
                    l2 = p2[m2].first;
                    r2 = p2[m2].second;
                    break;
                }
                p2[m2] = {cl, cr};
            }
            p[m1] = i;
        }
        if(l1 > l2) {
            swap(l1, l2);
            swap(r1, r2);
        }
        if(r1 > r2) {
            swap(r1, l2);
            swap(l2, r2);
        }
        if(r1 > l2) {
            swap(r1, l2);
        }
        l1 ++;
        l2 ++;
        cout << l1 << " " << r1 << " " << l2 << " " << r2 << "\n";
    }
    
    return 0;
}