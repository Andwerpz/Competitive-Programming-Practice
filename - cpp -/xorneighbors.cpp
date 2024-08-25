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

//AtCoder - ABC366G

//note that if there is a solution, then we can solve for each bit independently, as that's how XOR works. 

//since we want the assigned value for each node to be non-zero, for the ith node we can fix that it will
//have the ith bit as part of it's value. Then, we need to figure out some assignment of the ith bit to the
//rest of the nodes such that the xor sum of ith bits is good. 

//this assignment for the rest of the nodes can be done using gaussian elimination. At the end, we can
//just check whether or not our assignment is valid. 

void gauss_elim(vvb coeff, vb const_val, vb& soln) {
    if(coeff.size() == 0){
        return;
    }
    int cur = soln.size() - coeff.size();
    int n = coeff.size();
    // cout << "GAUSS ELIM : " << cur << endl;
    // for(int i = 0; i < n; i++){
    //     for(int j = 0; j < n; j++){
    //         cout << coeff[i][j] << " ";
    //     }
    //     cout << "= " << const_val[i] << "\n";
    // }
    if(coeff.size() == 1){
        soln[cur] = const_val[0];
        return;
    }
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
        if(ind == -1){
            ind = 0;
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
    gauss_elim(n_coeff, n_const_val, soln);
    bool val = const_val[ind];
    for(int i = 1; i < n; i++){
        if(coeff[ind][i]) {
            val = val ^ soln[i + cur];
        }
    }
    // cout << "ANS : " << cur << " " << val << " " << ind << "\n";
    soln[cur] = val;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vvi c(n);
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        a --;
        b --;
        c[a].push_back(b);
        c[b].push_back(a);
    }
    vl ans(n, 0);
    for(int i = 0; i < n; i++){
        // cout << "I : " << i << endl;
        int jptr = 0;
        vvb coeff(n - 1, vb(n - 1, 0));
        for(int j = 0; j < n; j++){
            if(j == i){
                continue;
            }
            for(int k = 0; k < c[j].size(); k++){
                int next = c[j][k];
                if(next == i){
                    continue;
                }
                coeff[next - (next > i? 1 : 0)][jptr] = true;
            }
            jptr ++;
        }
        // cout << "FIN COEFF" << endl;
        vb const_val(n - 1, 0);
        for(int j = 0; j < c[i].size(); j++){
            int next = c[i][j];
            const_val[next - (next > i? 1 : 0)] = true;
        }
        vb soln(n - 1, false);
        // cout << "FINISH CONSTRUCT" << endl;
        gauss_elim(coeff, const_val, soln);
        // cout << "SOLN : " << "\n";
        // for(int j = 0; j < n - 1; j++){
        //     for(int k = 0; k < n - 1; k++){
        //         cout << coeff[j][k] << " ";
        //     }
        //     cout << "\n";
        // }
        // for(int j = 0; j < n - 1; j++){
        //     cout << const_val[j] << " ";
        // }
        // cout << "\n";
        // for(int j = 0; j < n - 1; j++){
        //     cout << soln[j] << " ";
        // }
        // cout << "\n";
        for(int j = 0; j < n - 1; j++){
            if(soln[j]) {
                ans[j + (j >= i? 1 : 0)] += (1ll << i);
            }
        }
        ans[i] += (1ll << i);
    }
    bool is_valid = true;
    for(int i = 0; i < n; i++){
        ll sum = 0;
        for(int j = 0; j < c[i].size(); j++){
            sum ^= ans[c[i][j]];
        }
        is_valid = is_valid && sum == 0;
    }
    if(!is_valid) {
        cout << "No\n";
        return 0;
    }
    cout << "Yes\n";
    for(int i = 0; i < n; i++){
        cout << ans[i] << " ";
    }
    cout << "\n";
    
    return 0;
}