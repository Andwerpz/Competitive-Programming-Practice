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

//2024 ICPC NAQ - H

//first, the problem guarantees that the elements will be given in topologically sorted order, so
//that's nice. 

//first, we can fix for each creature, which parent it inherits its dominant gene from, and which parent
//it inherits its recessive gene from. From now on, i'll say that lp[i] = parent that i gets its 
//dominant gene from, and rp[i] = parent that i gets recessive gene. 

//d[i] = i's dominant gene, and r[i] = i's recessive gene. 

//each element will place restrictions on its parents (if its parents are known). Since the restrictions
//are placed on the parents, we'll evaluate it from bottom up (n -> 1). 
// - dominant gene
//   - d[lp[i]] == d[i] || r[lp[i]] == d[i] has to be true. Otherwise, if r[lp[i]] has not been assigned
//     assign r[lp[i]] := r[i]. Otherwise, this configuration is invalid. 
// - recessive gene
//   - if r[i] is assigned, can treat it like the dominant gene, but innherited from rp[i]. 
//   - else, r[rp[i]] has to be at least r[i]

//after placing all the restrictions, we can then assign unassigned values of r[i] in ascending order, 
//making sure that any values r[i] are consistent with the genes in rp[i]. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vvi par(n);
    vvi c(n);
    vector<char> dom(n);
    for(int i = 0; i < n; i++){
        int u, v;
        string d;
        cin >> u >> v >> d;
        u --;
        v --;
        par[i] = {u, v};
        if(u != -1){
            c[u].push_back(i);
            c[v].push_back(i);
        }
        dom[i] = d[0];
    }
    bool found = false;
    vector<string> best_found(0);
    for(int i = 0; i < (1 << n); i++){
        vi lp(n), rp(n);
        vi d(n), r(n, -1), h(n, 0);
        vb a(n, false);
        for(int j = 0; j < n; j++) {
            lp[j] = par[j][0];
            rp[j] = par[j][1];
            if((i >> j) & 1) {
                swap(lp[j], rp[j]);
            }
            d[j] = dom[j] - 'a';
        }
        bool is_valid = true;
        for(int j = n - 1; j >= 0; j--){
            if(lp[j] == -1){
                continue;
            }
            //dominant
            if(d[j] == d[lp[j]] || d[j] == r[lp[j]]) {
                //do nothing. 
            }
            else {  
                //need to set the recessive gene of the parent
                if(r[lp[j]] != -1){
                    is_valid = false;
                }
                else {
                    r[lp[j]] = d[j];    //this recessive gene needs to be set. 
                }
            }
            //recessive
            if(r[j] != -1){
                //this recessive gene is already set, treat it like dominant gene. 
                if(r[j] == d[rp[j]] || r[j] == r[rp[j]]) {
                    //do nothing.
                }
                else {
                    //need to set the recessive gene of the parent
                    if(r[rp[j]] != -1){
                        is_valid = false;
                    }
                    else {
                        r[rp[j]] = r[j];
                    }
                }
            }
            else {
                //otherwise, one of rp[j] alleles must be at least d[j].
                h[rp[j]] = max(h[rp[j]], d[j]);
            }
        }
        for(int j = 0; j < n; j++){
            if(r[j] == -1){
                r[j] = max(h[j], d[j]);
                if(lp[j] != -1){
                    if(r[j] <= d[rp[j]]) {
                        r[j] = d[rp[j]];
                    }
                    else if(r[j] <= r[rp[j]]) {
                        r[j] = r[rp[j]];
                    }
                }
            }
            if(lp[j] != -1){
                if(r[j] != d[rp[j]] && r[j] != r[rp[j]]) {
                    is_valid = false;
                }
            }
            if(r[j] < d[j]){
                is_valid = false;
            }
        }
        if(!is_valid){
            continue;
        }
        vector<string> ans(0);
        for(int j = 0; j < n; j++){
            string nxt = "  ";
            nxt[0] = 'a' + d[j];
            nxt[1] = 'a' + r[j];
            ans.push_back(nxt);
        }
        if(!found){
            found = true;
            best_found = ans;
        }
        if(ans < best_found){
            best_found = ans;
        }
    }
    if(!found){
        cout << "-1\n";
    }
    else {
        for(int i = 0; i < best_found.size(); i++) {
            cout << best_found[i] << "\n";
        }
    }
    
    return 0;
}