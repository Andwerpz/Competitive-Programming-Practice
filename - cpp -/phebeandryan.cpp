#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//2023 Columbia University Local Contest I

//casework. 

//figure out when one person can force the other one into k. 

void pari_forced(ll num_blocks) {
    if (num_blocks % 2 == 0) {
        cout << "RYAN" << endl;
    } else {
        cout << "PHEBE" << endl;
    } 
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, q; 
    cin >> n >> q;
    vector<ll> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    ll num_blocks = 0, totwei = 0;
    for (ll i = 1; i <= n; i++) {
        ll x = a[i];
        num_blocks += x;
        totwei += i * x;
    }
    set<pair<ll, int>> blocks;
    for (int i = 1; i <= n; i++) {
        blocks.insert({a[i], i});
    }
    while (q--) {
        string s; 
        cin >> s;
        if (s == "?") {
            ll k; cin >> k;
            if (k > totwei) {
                pari_forced(num_blocks);
            } 
            else if (k == totwei) {
                pari_forced(num_blocks + 1);
            } 
            else {
                ll freq = blocks.rbegin() -> first;
                ll wei = blocks.rbegin() -> second;
                ll diff = totwei - k;
                if (diff % wei != 0) {
                    pari_forced(num_blocks); 
                    continue;
                }
                ll rem_blocks = diff / wei;
                if (rem_blocks > freq) {
                    pari_forced(num_blocks);
                    continue; 
                }
                ll can_use = freq - rem_blocks;
                if (can_use < num_blocks - freq) {
                    pari_forced(num_blocks);
                    continue;
                }
                pari_forced(num_blocks - rem_blocks + 1); 
                
            }
        } 
        else {
            // set
            ll ind; cin >> ind;
            ll x; cin >> x;
            blocks.erase({a[ind], ind});
            num_blocks -= a[ind];
            totwei -= a[ind] * ind;
            a[ind] = x;
            num_blocks += a[ind];
            totwei += a[ind] * ind;
            blocks.insert({a[ind], ind});
        }
    }

    return 0;
}