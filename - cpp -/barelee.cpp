#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef std::pair<int, int> pii;
typedef std::pair<ll, ll> pll;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1369F

//for a given pair (s, e), I came up with the function to quickly compute whether or not you can force
//a win or loss given that you go first through trial and error (along with some hints from Josh, thanks 
//josh). The editorial has a proof, but i'm too lazy to read it. 

//notice that if the player to go first can't force a win, then it's always true that the second player
//can force a win. Likewise for forcing losses. 

//Determining whether or not you can force a win or a loss over a series of games is actually pretty
//easy. Just think about it for a moment and you'll get it. 

bool can_win(ll s, ll e) {
    if(e % 2 == 1){
        return (e - s) % 2;
    }
    bool filled = false;
    ll r = e;
    ll l = r / 2 + 1;
    while(s < l) {
        r = l - 1;
        l = r / 2 + 1;
        filled = !filled;
        if(!filled && r % 2 == 1){
            break;
        }
    }
    if(filled) {
        return true;
    }
    return (r - s) % 2;
}

bool can_lose(ll s, ll e) {
    bool filled = true;
    ll r = e;
    ll l = r / 2 + 1;
    while(s < l) {
        r = l - 1;
        l = r / 2 + 1;
        filled = !filled;
        if(!filled && r % 2 == 1) {
            break;
        }
    }
    if(filled) {
        return true;
    }
    return (r - s) % 2;
}

bool solve(vector<vector<bool>>& g, bool want_win) {
    for(int i = g.size() - 1; i >= 0; i--){
        want_win = !g[i][want_win];
    }
    return !want_win;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n;
    cin >> n;
    vector<pll> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i].first >> a[i].second;
    }
    vector<vector<bool>> g(n, vector<bool>(2));
    for(int i = 0; i < n; i++){
        g[i][0] = can_lose(a[i].first, a[i].second);
        g[i][1] = can_win(a[i].first, a[i].second);
    }
    cout << solve(g, true) << " " << solve(g, false) << "\n";
    
    //e is even:
    //start from e and split into segments
    //l = floor(r / 2) + 1. 
    //in other words, least element that when multiplied by 2 is still greater than r. 
    //even indexed segments always start with 0 and alternate, odd indexed segments are all non-zero
    //e is odd:
    //everything alternates

    // int e;
    // cin >> e;
    // vector<vector<bool>> g(e + 1, vector<bool>(2)); //0 = force loss, 1 = force win
    // for(int i = e; i >= 0; i--){
    //     {   
    //         g[i][0] = false;
    //         if(i * 2 > e || !g[i * 2][0]) {
    //             g[i][0] = true;
    //         }
    //         if(i + 1 > e || !g[i + 1][0]) {
    //             g[i][0] = true;
    //         }
    //     }
    //     {   
    //         g[i][1] = false;
    //         if(i * 2 <= e && !g[i * 2][1]) {
    //             g[i][1] = true;
    //         }
    //         if(i + 1 <= e && !g[i + 1][1]) {
    //             g[i][1] = true;
    //         }
    //     }
    // }
    // for(int i = 1; i <= e; i++){
    //     cout << "I : " << i << ", " << g[i][0] << " " << can_lose(i, e) << "\n";
    // }
    // cout << "\n";
    // for(int i = 1; i <= e; i++){
    //     cout << "I : " << i << ", " << g[i][1] << " " << can_win(i, e) << "\n";
    // }
    
    return 0;
}