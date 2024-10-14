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

//Codeforces - 1903 D1 D2

//very tricky SOS dp problem. 

//for the easy version, it's sufficient to greedily construct the answer to each query in O(n * log(a)) time. 
//just consider every bit in descending order, and test to see how much it'll cost. 

//for the hard version, we want to optimize finding the answer to some k to O(log(a)) time. Consider building some
//answer ans, and it starts at 0. If we add some bit b, then the next answer or nans = ans + 2^b. How will the cost 
//change?

//let's consider every a[i] individually.
//1. nans is a subset of a[i]. Cost doesn't change because it's 0 for this a[i]
//2. ans is a subset of a[i], but nans is not. We'll have to raise up everything in a[i] below 2^b, so the cost
//   is 2^b - (a[i] % 2^b). 
//3. ans is not a subset of a[i]. Since we've already done the 'raising up' described in the second case, everything 
//   below 2^b in this case is 0, therefore we have 2^b cost. 

//if we can precompute dpa[i] = number of j such that i is a subset of a[j], and 
//dpb[b][i] = sum of a[j] % 2^b such that i is a subset of a[j], then we can quickly compute each query in O(log(a))
//time. Luckily, these two can be efficiently computed using SOS dp. 

//note that if k > n * 10^6, then we can directly compute the answer as floor((k + sum(a)) / n). This means that 
//we only need to consider the first 20 or so bits, as if the answer has above 20 bits then we can compute it 
//using this method. As the time and mem limit is pretty tight, this optimization is necessary to AC. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int BITS = 21;
    int n, q;
    cin >> n >> q;
    vl a(n), dpa((1 << BITS), 0);   //dpa[i] = how many elements in a is i a subset of
    vvl dpb(BITS, vl((1 << BITS), 0));  //dpb[b][i] = sum of a[j] % 2^b where i is subset of a[j]
    ll sum = 0;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        dpa[a[i]] += 1;
        for(int j = 0; j < BITS; j++){
            dpb[j][a[i]] += a[i] % (1 << j);
        }
        sum += a[i];
    }
    for(int i = 0; i < BITS; i++){
        for(int j = 0; j < (1 << BITS); j++){
            if((j & (1 << i)) == 0) {
                dpa[j] += dpa[j ^ (1 << i)];
            }
        }
    }
    for(int b = 0; b < BITS; b++){
        for(int i = 0; i < BITS; i++){
            for(int j = 0; j < (1 << BITS); j++){
                if((j & (1 << i)) == 0){
                    dpb[b][j] += dpb[b][j ^ (1 << i)];
                }
            }
        }
    }
    for(int i = 0; i < q; i++){
        ll k;
        cin >> k;
        if(k > n * 1e6) {
            //directly compute answer
            ll ans = (k + sum) / n;
            cout << ans << "\n";
        }
        else {
            int ans = 0;
            ll scnt = 0;   //initially, nothing doesn't have 0 as a subset
            for(int j = BITS - 1; j >= 0; j--){
                //test adding on jth bit
                int nans = ans + (1 << j);
                ll diff = dpa[ans] - dpa[nans];
                ll n_scnt = scnt + diff;
                ll nk = k;
                //need to add 2^j to all initially scnt
                //numbers that already don't have ans as submask have all 0s before (1 << j). 
                nk -= scnt * (1 << j);
                //for elements that are newly scnt, need to add their increase sum
                //dpb[j][ans] - dpb[j][nans] is exactly the sum of numbers that have ans as a submask, but don't have ans ^ (1 << j).
                nk -= (1 << j) * diff - (dpb[j][ans] - dpb[j][nans]);
                if(nk >= 0){
                    k = nk;
                    ans = nans;
                    scnt = n_scnt;
                }
            }
            cout << ans << "\n";
        }
    }

    //easy version solution
    // for(int i = 0; i < q; i++){
    //     ll _k;
    //     cin >> _k;
    //     vl tmp = a;
    //     ll ans = 0;
    //     for(int j = 60; j >= 0; j--){
    //         ll cost = 0;
    //         ll bit = (1ll << j);
    //         for(int k = 0; k < n && cost <= _k; k++){
    //             if(tmp[k] < bit) {
    //                 cost += bit - tmp[k];
    //             }
    //         }
    //         if(cost <= _k) {
    //             _k -= cost;
    //             ans += bit;
    //             // cout << "ANSBIT : " << bit << " " << cost << "\n";
    //             for(int k = 0; k < n; k++){
    //                 tmp[k] = max(0ll, tmp[k] - bit);
    //             }
    //         }
    //         else {
    //             for(int k = 0; k < n; k++){
    //                 if(tmp[k] >= bit) {
    //                     tmp[k] -= bit;
    //                 }
    //             }
    //         }
    //     }
    //     cout << ans << "\n";
    // }
    
    return 0;
}

// -- observation forces
// void print_bin(int val) {
//     for(int i = 30; i >= 0; i--){
//         cout << ((val >> i) & 1);
//     }
//     cout << "\n";
// }

// int calc_cost(int val, int tgt) {
//     int ans = 0;
//     while((val & tgt) != tgt) {
//         val ++;
//         ans ++;
//     }
//     return ans;
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL); cout.tie(NULL);
    
//     int n = 31;
//     for(int i = 0; i <= n; i++){
//         for(int j = 0; j < i; j++){
//             cout << calc_cost(i, j) << " ";
//         }
//         cout << "\n";
//     }
    
//     return 0;
// }