#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1837E

//simple counting problem. (eh, maybe not so simple, idk how i figured out how to actually do the counting.)

//lets first consider the case where we can place the teams wherever we want; in other words, all entries are -1. 
//observe that if we want all the weak teams to finish last, then we cannot place two weak teams next to each other, 
//and similar logic applies for the next weakest teams. 

//we can figure out a way to build any seed that follows the rules. We place the teams into their places from the weakest to
//the strongest. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int k;
    cin >> k;
    int n = (1 << k);
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    int len = 2;
    ll ans = 1;
    ll mod = 998244353;
    int l = n;
    int r = n / 2;
    while(len <= n){
        //cout << "LR : " << l << " " << r << "\n";
        int nrneg = 0;
        for(int i = 0; i < n; i += len) {
            bool found = false;
            int negind = -1;
            int negamt = 0;
            for(int j = i; j < i + len; j++){
                if(l >= a[j] && a[j] > r) {
                    if(found) {
                        ans = 0;
                    }
                    found = true;
                }
                if(a[j] == -1){
                    negind = j;
                    negamt ++;
                }
            }
            //cout << len << " " << i << " " << found << " " << negind << " " << negamt << "\n";
            if(!found && negind == -1){
                ans = 0;
            }
            else {
                ans *= (found? 1 : negamt);
                ans %= mod;
                if(!found) {
                    a[negind] = l;
                    nrneg ++;
                }
            }
        }
        for(int i = 1; i <= nrneg; i++){
            ans *= i;
            ans %= mod;
        }
        l >>= 1;
        r >>= 1;
        len <<= 1;
    }
    cout << ans << "\n";
    
    return 0;
}
