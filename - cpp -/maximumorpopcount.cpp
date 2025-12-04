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

//Codeforces - 2147E

//first, observe that if we set some bit k that doesn't exist in the popcount, then it's always cheaper 
//to just set all bits less than k. 

//can observe this is true even in the 1 number case as to set the kth bit, you first need to increment until
//all bits under k are set. 

//next, I guess that it's always optimal to pick some k, and set all bits under that k. This is kinda intuitive,
//but I still lack a proof. So now, for each k we need to figure out the minimum cost to do this. 

//we can compute this using a greedy strategy. Iterate through the bits under k from most to least significant
//until you find one that's not set. Then, go through all the numbers and find the one with the least cost to make
//that bit set. Increment the minimum cost number, and continue iterating through the bits. 

//now to solve the queries, we can populate cost where cost[i] = min cost of having popcount = i. 

const int B = 32;
vi calc_f(vl& a) {
    int n = a.size();
    vi f(B, 0);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < B; j++) {
            if((a[i] >> j) & 1) f[j] ++;
        }
    }
    return f;
}

int f_popcount(vi& f) {
    int popcnt = 0;
    for(int i = 0; i < B; i++) if(f[i]) popcnt ++;
    return popcnt;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, q;
        cin >> n >> q;
        vl a(n);
        for(int i = 0; i < n; i++) cin >> a[i];
        vl cost(B, 1e18);   //cost[i] = minimum cost of having or popcount == i
        //0 cost
        {
            vi f = calc_f(a);
            cost[f_popcount(f)] = 0;
        }
        //set all i least significant bits
        for(int i = 0; i < B; i++) {
            vl tmpa = a;
            vi f = calc_f(a);
            ll ccost = 0;
            for(int j = i; j >= 0; j--) {
                if(f[j]) continue;
                //need to set this one, find number to increment with least cost. 
                int ind = -1;
                ll inccost = 1e18;
                for(int k = 0; k < n; k++) {
                    ll cinccost = (1ll << j) - (tmpa[k] & ((1ll << j) - 1));
                    if(cinccost < inccost) {
                        inccost = cinccost;
                        ind = k;
                    }
                }
                assert(ind != -1);
                for(int k = 0; k < B; k++) if((tmpa[ind] >> k) & 1) f[k] --;
                tmpa[ind] += inccost;
                for(int k = 0; k < B; k++) if((tmpa[ind] >> k) & 1) f[k] ++;
                ccost += inccost;
            }
            int popcount = f_popcount(f);
            cost[popcount] = min(cost[popcount], ccost);
        }
        for(int i = B - 2; i >= 0; i--) cost[i] = min(cost[i], cost[i + 1]);
        // cout << "COST :\n";
        // for(int i = 0; i < B; i++) cout << cost[i] << "\n";
        for(int i = 0; i < q; i++) {
            ll b;
            cin >> b;
            int ans = 0;
            for(int j = 0; j < B; j++) {
                if(cost[j] > b) break;
                ans = j;
            }
            cout << ans << "\n";
        }
    }
    
    return 0;
}