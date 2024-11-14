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

//Meta Hacker Cup 2024 Round 2 - B

//tricky brute force backtracking problem. 

//note that there are only 7^7 possible states, as we can decide on a height for each column. 
//we can simply do dp over all of these possible states to see what winning states are directly visitable 
//from the starting state. 

//the tricky part is that we also need to make sure any winning states have a path to the ending state,
//and we can precompute this pretty easily for all states. 

int n = 6;
int m = 7;

int get_height(int ind, int col) {
    return (ind >> (col * 3)) & 7;
}

vi dr = {-1, -1, -1, 0, 1, 1, 1, 0};
vi dc = {-1, 0, 1, 1, 1, 0, -1, -1};

//what wins can we get to directly from this state?
pii calc_dp(int ind, vector<pii>& dp, vi& v, vector<string>& g, bool c_turn) {
    if(dp[ind].first != -1){
        return dp[ind];
    }
    pii ans = {0, 0};
    //decide what move to do
    for(int i = 0; i < m; i++){
        int h = get_height(ind, i);
        if(h == n) {    //column full
            continue;
        }
        if((g[h][i] == 'C') != c_turn) {  //turn doesn't match up
            continue;
        }
        int nind = ind;
        nind = nind & ~(7 << (i * 3));
        nind = nind | ((h + 1) << (i * 3));
        if(!v[nind]){   //can't get to end from here if we do this move
            continue;
        }
        //see if we win here
        vi ext(8, 0);
        for(int j = 0; j < 8; j++){
            for(int k = 1; k <= 3; k++) {
                int nr = h + dr[j] * k;
                int nc = i + dc[j] * k;
                if(nr < 0 || nc < 0 || nr >= n || nc >= m){
                    break;
                }
                if(nr >= get_height(ind, nc)) {
                    break;
                }
                if((g[nr][nc] == 'C') != c_turn) {
                    break;
                }
                ext[j] ++;
            }
        }
        bool wins = false;
        for(int j = 0; j < 4; j++){
            if(ext[j] + ext[j + 4] >= 3){
                wins = true;
            }
        }
        if(wins){
            // cout << "FOUND WIN : " << ind << "\n";
            if(c_turn){
                // cout << "FOUND CWIN : " << ind << " " << g[h][i] << "\n";
                // for(int j = 0; j < m; j++){
                //     cout << get_height(ind, j) << " ";
                // }
                // cout << "\n";
                // for(int j = 0; j < 8; j++){
                //     cout << ext[j] << " ";
                // }
                // cout << "\n";
                ans.first = true;
            }
            else {
                ans.second = true;
            }
        }
        else {
            //if we don't win, then just recurse
            pii nans = calc_dp(nind, dp, v, g, !c_turn);
            ans.first = max(ans.first, nans.first);
            ans.second = max(ans.second, nans.second);
        }
    }
    // cout << "DP : " << ind << " " << ans.first << " " << ans.second << "\n";
    dp[ind] = ans;
    return ans;
}

int can_re(int ind, vi& v, vector<string>& g, bool c_turn) {
    if(v[ind] != -1){
        return v[ind];
    }
    bool is_end = true;
    bool ans = false;
    for(int i = 0; i < m; i++){
        int h = get_height(ind, i);
        if(h == n){
            continue;
        }
        is_end = false;
        if((g[h][i] == 'C') != c_turn) {
            continue;
        }
        int nind = ind;
        nind = nind & ~(7 << (i * 3));
        nind = nind | ((h + 1) << (i * 3));
        ans = can_re(nind, v, g, !c_turn) || ans;
    }
    if(is_end){
        v[ind] = 1;
        return 1;
    }
    v[ind] = ans;
    return v[ind];
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ifstream in("--in--.txt");
    streambuf *cinbuf = cin.rdbuf(); //save old buf
    cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
    
    ofstream out("--out--.txt");
    streambuf *coutbuf = cout.rdbuf(); //save old buf
    cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

    int t;
    cin >> t;
    int casi = 0;
    while(t--){
        casi ++;
        vector<string> g(n);
        for(int i = 0; i < n; i++){
            cin >> g[i];
        }
        reverse(g.begin(), g.end());
        vector<pii> dp((1 << 21), {-1, -1});    //{C, F}
        vi v((1 << 21), -1);
        can_re(0, v, g, true);
        calc_dp(0, dp, v, g, true);
        string ans;
        if(dp[0].first == dp[0].second){
            if(dp[0].first) {
                ans = "?";
            }
            else {
                ans = "0";
            }
        }
        else {
            if(dp[0].first) {
                ans = "C";
            }
            else {
                ans = "F";
            }
        }
        cout << "Case #" << casi << ": " << ans << "\n";
    }
    
    return 0;
}