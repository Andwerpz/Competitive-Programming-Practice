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

//returns false if there is no solution
bool gauss_elim(vvb coeff, vb const_val, vb& soln) {
    int cur = soln.size() - coeff.size();
    if(coeff.size() == 1){
        if(!coeff[0][0]) {
            return false;
        }
        soln[cur] = const_val[cur];
        return true;
    }
    int n = coeff.size();
    int ind = -1;
    for(int i = 0; i < n; i++){
        if(coeff[i][0]){
            ind = i;
            break;
        }
    }
    if(ind == -1){
        for(int i = 0; i < n; i++){
            bool empty = true;
            for(int j = 0; j < n; j++){
                if(coeff[i][j]){
                    empty = false;
                }
            }
            if(empty) {
                ind = i;
                break;
            }
        }
    }
    vvb n_coeff(n - 1, vb(n - 1, false));
    vb n_const_val(n - 1, false);
    int iptr = 0;
    for(int i = 0; i < n; i++){
        if(i == ind){
            continue;
        }
        n_const_val[iptr] = const_val[i];
        for(int j = 1; j < n; j++){
            n_coeff[iptr][j - 1] = coeff[i][j];
        }
        if(coeff[i][0]) {
            n_const_val[iptr] = n_const_val[iptr] ^ const_val[ind];
            for(int j = 1; j < n; j++){
                n_coeff[iptr][j - 1] = n_coeff[iptr][j - 1] ^ coeff[ind][j];
            }
        }
        iptr ++;
    }
    bool has_soln = gauss_elim(n_coeff, n_const_val, soln);
    if(!has_soln) {
        return false;
    }
    bool val = const_val[ind];
    for(int i = 1; i < n; i++){
        if(coeff[ind][i]) {
            val = val ^ soln[i];
        }
    }
    soln[cur] = val;
    return true;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    
    
    return 0;
}