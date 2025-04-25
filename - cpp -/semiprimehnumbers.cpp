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

//Kattis - hnumbers

//first, write an algorithm to find all h-prime numbers. 

//then observe that the numbers that we're trying to find (h-semiprime) must be able to be written as a product of 
//exactly 2 h-prime numbers. There aren't actually that many h-prime numbers under 1e6 + 1 (around 90000), so we
//can just try all pairs such that the product is <= 1e6 + 1. 

//then, each query can be answered in O(1). 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    const int N = 1e6 + 1;
    vb ispr(N + 1, true);
    vl pr;
    ispr[1] = false;
    for(int i = 5; i <= N; i += 4){
        if(ispr[i]) {
            pr.push_back(i);
            for(int j = 5; i * j <= N; j += 4) {
                ispr[i * j] = false;
            }
        }
    }
    vi cnt(N + 1, 0);
    for(int i = 0; i < pr.size(); i++){
        for(int j = i; j < pr.size(); j++){
            if(pr[i] * pr[j] > N) break;
            cnt[pr[i] * pr[j]] ++;
        }
    }
    vi ans(N + 1, 0);
    for(int i = 0; i <= N; i++){
        if(cnt[i]) {
            ans[i] = 1;
        }
    }
    for(int i = 1; i <= N; i++) ans[i] += ans[i - 1];
    int h;
    cin >> h;
    while(h != 0) {
        cout << h << " " << ans[h] << "\n";
        cin >> h;
    }
    
    return 0;
}