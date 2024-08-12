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

//Codeforces - 1998C

//apparently, you only need to try removing the maximum element where b[i] = 1, and b[i] = 0. 
//i tried everything, resulting in a much more difficult implementation. 

bool is_valid(vl& mod, vl& mod_pfx, vl& nomod, ll k, int rm_ind, bool rm_mod, ll val) {
    int n = mod.size() + nomod.size() - 1;
    int req = (n + 2) / 2;
    if(nomod.size() != 0){
        int low = 0;
        int high = (int) nomod.size() - 1;
        int ind = nomod.size();
        while(low <= high) {
            int mid = low + (high - low) / 2;
            if(nomod[mid] >= val) {
                ind = min(ind, mid);
                high = mid - 1;
            }
            else {
                low = mid + 1;
            }
        }
        req -= nomod.size() - ind;
        if(!rm_mod && rm_ind >= ind) {
            req ++;
        }
    }
    if(req <= 0){
        return true;
    }
    if(req > mod.size() - rm_mod) {
        return false;
    }
    int r = mod.size();
    {
        int low = 0;
        int high = (int) mod.size() - 1;
        while(low <= high) {
            int mid = low + (high - low) / 2;
            if(mod[mid] >= val) {
                r = min(r, mid);
                high = mid - 1;
            }
            else {
                low = mid + 1;
            }
        }
        req -= mod.size() - r;
        if(rm_mod && rm_ind >= r) {
            req ++;
        }
    }
    if(req <= 0){
        return true;
    }
    int l = r - req;
    ll sum = mod_pfx[r] - mod_pfx[l];
    if(rm_mod && rm_ind >= l && rm_ind < r) {
        sum += mod[l - 1] - mod[rm_ind];
    }
    ll req_k = val * req - sum;
    return k >= req_k;
}

//returns max median + leftover k
ll calc_max_median(vl& mod, vl& mod_pfx, vl& nomod, ll k, int rm_ind, bool rm_mod) {
    ll low = 0;
    ll high = 1e9 + 100;
    ll ans = low;
    while(low <= high) {
        ll mid = low + (high - low) / 2;
        if(is_valid(mod, mod_pfx, nomod, k, rm_ind, rm_mod, mid)) {
            ans = max(ans, mid);
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        vl a(n), b(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        for(int i = 0; i < n; i++){
            cin >> b[i];
        }
        vl mod(0), nomod(0);
        for(int i = 0; i < n; i++){
            if(b[i]){
                mod.push_back(a[i]);
            }
            else {
                nomod.push_back(a[i]);
            }
        }
        sort(mod.begin(), mod.end());
        sort(nomod.begin(), nomod.end());
        vl mod_pfx(mod.size() + 1, 0);
        for(int i = 1; i <= mod.size(); i++){
            mod_pfx[i] = mod_pfx[i - 1] + mod[i - 1];
        }
        ll ans = 0;
        for(int i = 0; i < mod.size(); i++){
            ans = max(ans, calc_max_median(mod, mod_pfx, nomod, 0, i, true) + mod[i] + k);
        }
        for(int i = 0; i < nomod.size(); i++){  
            ans = max(ans, calc_max_median(mod, mod_pfx, nomod, k, i, false) + nomod[i]);
        }
        cout << ans << "\n";
    }
    
    return 0;
}