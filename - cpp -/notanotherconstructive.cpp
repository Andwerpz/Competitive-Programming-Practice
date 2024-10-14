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

//2024 ICPC NAC - I

//consider a naive dp: dp[i][ncnt][nacnt][naccnt] = is visitable where
//i = length of prefix
//ncnt = number of 'n's, nacnt = number of 'na's, naccnt = number of 'nac's. 
//transitions are pretty obvious, but the problem is that it'll TLE. 

//however, if you think about the number of actually visitable states, it's probably going to be way less than the naive
//estimate, and yes, it turns out to be around 46 million. This might actually be recursive backtrackable. 

//If we want to do recursive backtracking, we'll need a way to prune the search tree. We'll have all the usual pruning
//such as if naccnt goes over k, and if i goes over n, but the big boy pruning is checking whether it's possible
//with optimal 'N' 'A' and 'C' placement to get to k 'NAC's. 

//since this pruning knocks out quite alot of the search tree, we can just try all possible amounts of 'N', 'A', and 'C's
//via brute force. 

string ans = "";
set<ll> v;
bool solve(int ind, int ncnt, int nacnt, int naccnt, int k, string& s, string& cur){
    if(naccnt == k && ind == s.size()){
        ans = cur;
        return true;
    }
    if(naccnt > k || ind == s.size()){
        return false;
    }
    ll hash = (((ll) ind) << 0) ^ (((ll) ncnt) << 15) ^ (((ll) nacnt) << 30) ^ (((ll) naccnt) << 45);
    if(v.count(hash)) {
        return false;
    }
    v.insert(hash);
    { 
        int rem = s.size() - ind;
        int mx_poss = naccnt;
        for(int i = 0; i <= rem; i++){
            for(int j = 0; j + i <= rem; j++){
                int n_ncnt = ncnt + i;
                int n_nacnt = nacnt + n_ncnt * j;
                int n_naccnt = naccnt + n_nacnt * (rem - i - j);
                mx_poss = max(mx_poss, n_naccnt);
            }
        }
        if(mx_poss < k){
            return false;
        }
    }
    if(s[ind] == 'N' || s[ind] == '?') {
        cur.push_back('N'); 
        if(solve(ind + 1, ncnt + 1, nacnt, naccnt, k, s, cur)) {
            return true;
        }
        cur.pop_back();
    }
    if(s[ind] == 'A' || s[ind] == '?') {
        cur.push_back('A'); 
        if(solve(ind + 1, ncnt, nacnt + ncnt, naccnt, k, s, cur)) {
            return true;
        }
        cur.pop_back();
    }
    if(s[ind] == 'C' || s[ind] == '?') {
        cur.push_back('C'); 
        if(solve(ind + 1, ncnt, nacnt, naccnt + nacnt, k, s, cur)) {
            return true;
        }
        cur.pop_back();
    }
    if((s[ind] != 'N' && s[ind] != 'A' && s[ind] != 'C') || s[ind] == '?') {
        cur.push_back(s[ind] == '?'? 'T' : s[ind]); 
        if(solve(ind + 1, ncnt, nacnt, naccnt, k, s, cur)) {
            return true;
        }
        cur.pop_back();
    }
    return false;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    string cur = "";
    solve(0, 0, 0, 0, k, s, cur);
    cout << "VCNT : " << v.size() << "\n";
    if(ans.size() == 0){
        cout << "-1\n";
    }
    else {
        cout << ans << "\n";
    }
    
    return 0;
}