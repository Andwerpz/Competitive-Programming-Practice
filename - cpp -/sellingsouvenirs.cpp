#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 808E

//Of course, we always want to greedily pick the items with the most value if they are 
//of the same weight, so we first sort the elements by descending order of value within their
//weight type. 

//instead of having 3 types of weights, consider the case where there are only 2 types. There, 
//we can pretty obviously solve the problem in linear time by first fixing the amount of weight type
//1 you bring, and then the amount of weight type 2 items will be determined. 

//Now for the current problem with 3 types of weights, it seems like we have to fix 2 amounts
//to compute the answer, but we can be more clever than that. 

//Denote the most value we can bring given that we've fixed that we're bringing x weight 3 items
//as A(x). I claim that A(x) will be unimodal (idk exactly why, i'm just going off of intuition
//here). Thus, we can just ternary search over all x, giving us O(n * log(n)) complexity. 

//The editorial describes a much more elegant dp approach which gets a O(n) complexity, and omits 
//alot of my guesswork. 

ll calc(vector<vector<ll>>& c, int m) {
    ll ans = 0;
    for(int i = 0; i < c[1].size(); i++){
        int rem = min((int) c[0].size() - 1, m - i * 2);
        if(rem < 0){
            break;
        }
        ans = max(ans, c[1][i] + c[0][rem]);
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<vector<ll>> c(3, vector<ll>(0));
    for(int i = 0; i < n; i++){
        ll w, cost;
        cin >> w >> cost;
        c[w - 1].push_back(cost);
    }
    for(int i = 0; i < 3; i++){
        sort(c[i].begin(), c[i].end());
        reverse(c[i].begin(), c[i].end());
        c[i].insert(c[i].begin(), 0);
        for(int j = 1; j < c[i].size(); j++){
            c[i][j] += c[i][j - 1];
        }
    }
    //ternary search across weight 3?
    int low = 0;
    int high = min((int) c[2].size() - 1, m / 3);
    while(high - low > 5) {
        int m0 = low + (high - low) * 1 / 3;
        int m1 = low + (high - low) * 2 / 3;
        ll a0 = c[2][m0] + calc(c, m - 3 * m0);
        ll a1 = c[2][m1] + calc(c, m - 3 * m1);
        if(a0 > a1) {
            high = m1;
        }
        else {
            low = m0;
        }
    }
    ll ans = 0;
    for(int i = low; i <= high; i++){
        ans = max(ans, c[2][i] + calc(c, m - 3 * i));
    }
    cout << ans << "\n";
    
    return 0;
}