#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<int, int>;
#define rep(i, a, b) for (int i = a; i < b; ++i)

//The 3rd Universal Cup. Stage 18: Southeastern Europe - K

//we can use sqrt decomposition. When handling the doubling query, on the buckets that are completely covered by the query, 
//we can just keep track of how many times we should double it via some lazy change. On the print character query, we can
//just iterate through the buckets in O(sqrt(n)) time. 

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int n, q; cin >> n >> q;
    string s; cin >> s;

    int len = sqrt(n);
    vector<ll> a(n), bucks((n / len) + 1, 0), dobls((n / len) + 1);

    for (int i = 0; i < n; ++i) {
        // cin >> a[i];
        a[i] = 1;
        bucks[i / len]++;
        dobls[i / len] = 1;
    }
    // cerr << "len : " << len << endl;

    auto apply_lazy = [&](int idx) -> void {
        // assert(0 <= idx && idx < bucks.size());
        if (dobls[idx] == 1)
            return;
        
        // cerr << "apply lazy : " << idx << endl;
        // cerr << "L R : " << idx * len << " " << (idx + 1) * len
        rep(i, idx * len, min(n, (idx + 1) * len)) {
            a[i] *= dobls[idx];
            // cerr << a[i] << "," << i << " ";
        }
        // cerr << "\n";
        bucks[idx] *= dobls[idx];
        dobls[idx] = 1;
    };

    auto find = [&](ll target) -> pair<int, ll> {
        // cerr << "TARGET : " << target << endl;
        // takes in idx, spits back index in A
        ll idx = 0;
        int buck_idx = 0;
        while (idx + bucks[buck_idx] * dobls[buck_idx] <= target) {
            idx += bucks[buck_idx] * dobls[buck_idx];
            buck_idx++;
        }

        // have bucket idx
        // keep going
        apply_lazy(buck_idx);
        int within = 0;
        while (idx + a[len * buck_idx + within] <= target) {
            idx += a[len * buck_idx + within];
            within ++;
        }

        // assert(len * buck_idx + within < n);
        // cout << "IND : " << len * buck_idx + within << "\n";

        // cerr << "buck_idx : " << buck_idx << " within : " << within << endl;
        // cerr << "IDX : " << idx << endl;
        return {len * buck_idx + within, idx};
        
    };

    
    // cerr << "hey" << endl; 

    // for (auto x : bucks) {
    //     cerr << x << " ";
    // }
    // cerr << endl;

    // ll strlen = n;
    while (q--) {
        int typ; cin >> typ;
        // int typ = 1;
        if (typ == 1) {
            ll l, r; cin >> l >> r;
            l--, r--;

            // ll l = rand() % strlen, r = rand() % strlen;
            // if(r < l) swap(l, r);
            // strlen += r - l + 1;

            // cerr << "L : " << l << " R : " << r << endl;
            
            pair<int, ll> l_info = find(l), r_info = find(r);
            int l_idx = l_info.first, r_idx = r_info.first;
            ll l_off = l_info.second, r_off = r_info.second;
            // double everything in between
            rep(i, (l_idx/len)+1, (r_idx / len)) {
                // cerr << "DBL. i : " << i << endl;
                dobls[i] *= 2;
            }

            // check edges
            apply_lazy(l_idx / len), apply_lazy(r_idx / len);
            
            // propagate doubles to edge buckets
            
            if (l_idx / len == r_idx / len) {
                rep(i, l_idx+1, r_idx) {
                    bucks[i / len] += a[i];
                    a[i] *= 2;
                }
            } else {
                rep(i, l_idx+1, (l_idx / len + 1) * len) {
                    // cerr << "PROP L : " << i << endl;
                    bucks[i / len] += a[i];
                    a[i] *= 2;
                }

                rep(i, (r_idx / len) * len, r_idx) {
                    // cerr << "PROP R : " << i << endl;
                    bucks[i / len] += a[i];
                    a[i] *= 2;
                }
            }
            if (l_idx != r_idx) {
                // handle l_idx
                // cerr << "loff, roff : " << l_off << " " << r_off << endl;
                // cerr << "lidx ridx " << l_idx << " " << r_idx << endl;
                bucks[l_idx / len] += (a[l_idx] - (l - l_off));
                a[l_idx] += (a[l_idx] - (l - l_off));
                bucks[r_idx / len] += (r - r_off + 1);
                a[r_idx] += (r - r_off + 1);
            } else {
                bucks[l_idx / len] += (r - l + 1);
                a[l_idx] += (r - l + 1);
            }

            // strlen = 0;
            // for(int i = 0; i < bucks.size(); i++) {
            //     // cerr << bucks[i] << "," << dobls[i] << " ";
            //     strlen += bucks[i] * dobls[i];
            // }
            // cerr << "\n";
            // for(int i = 0; i < strlen; i++) {
            //     int ind = find(i).first;
            //     cerr << s[ind];
            // }
            // cerr << "\n";
            // find(strlen - 1);

        } else {
            ll x; cin >> x;
            x--;
            int idx = find(x).first;
            // cerr << "idx : " << idx << endl;
            cout << s[idx] << "\n";
        }
    }

    // for (auto x : bucks) {
    //     cerr << x << " ";
    // }
    // cerr << endl;
    
    return 0;
}