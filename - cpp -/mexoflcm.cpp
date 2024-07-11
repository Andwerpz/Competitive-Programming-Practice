#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1834E

//first, notice that since there are at most n^2 distinct subarrays, the mex cannot be larger
//than n^2 + 1. 

//second, for a given left point l, how many different LCMs can we generate if we are allowed to 
//freely vary the right point? Turns out actually only around log(n). 

//denote the list of unique LCMs that we can generate given some left point as L. Next, 
//sort L in ascending order, so that L[i] < L[i + 1]. Due to the way that LCM works, 
//L[i] | L[i + 1] must also be true. This means that every successive greater LCM must
//be a multiple of the previous one, and if we only want to generate LCMs up to n^2, 
//then we'll have at most log(n^2) or 2 * log(n) unique LCMs.

//now how do we actually generate the LCMs? Consider that you have L for some left bound l. Then, 
//we want to move l to l - 1. We can simply add a[l - 1] to the set, and then apply 
//L[i] := lcm(L[i], a[l - 1]) to all the elements in L.

//Since for all left bounds, there are at most log(n) LCMs, we can simply aggregate them all
//and take the MEX. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        ll n;
        cin >> n;
        vector<ll> a(0);
        for(int i = 0; i < n; i++){
            int next;
            cin >> next;
            if(a.size() == 0 || *a.rbegin() != next) {
                a.push_back(next);
            }
        }
        n = a.size();
        vector<ll> b(0);
        set<ll> s;
        for(int i = 0; i < n; i++){
            set<ll> tmp;
            tmp.insert(a[i]);
            for(auto j = s.begin(); j != s.end(); j++){
                ll nxt = *j * a[i] / gcd(*j, a[i]);
                if(nxt <= n * n) {
                    tmp.insert(nxt);
                }
            }
            s = tmp;
            for(auto j = s.begin(); j != s.end(); j++){
                b.push_back(*j);
            }
        }
        sort(b.begin(), b.end());
        // cout << "B : ";
        // for(int i = 0; i < b.size(); i++){
        //     cout << b[i] << " ";
        // }
        // cout << "\n";
        ll mex = *b.rbegin() + 1;
        for(int i = 1; i < b.size(); i++){
            if(b[i] - 1 > b[i - 1]) {
                mex = b[i - 1] + 1;
                break;
            }
        }
        if(b[0] != 1) {
            mex = 1;
        }
        cout << mex << "\n";
    }
    
    return 0;
}