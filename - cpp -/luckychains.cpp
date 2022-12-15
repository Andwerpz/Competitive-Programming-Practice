#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1766D

//we want to find the smallest positive a where gcd(l + a, r + a) != 1

//assume that l < r. d = r - l. 

//note that if d == 1, then a doesn't exist, since gcd(x, x + 1) = 1. In this case, the chain will be infinitely long. 

//else, we just have to wait for l + a and r + a to share a common factor with d. We can find the list of factors
//of d; f, and for each factor, f[i], check how many +1s it will take to make l become a multiple of it; f[i] - (l % f[i]). 

//the answer is simply the minimum out of all of these. Miniumum and not maximum since the chain will break when l first shares a factor
//with d. 

//note that if l shares a factor with d, then r has to share a factor. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    const int N = 10000000;
    vector<int> lpf(N+1);
    vector<int> p;
    for (int i=2; i <= N; ++i) {
        if (lpf[i] == 0) {
            lpf[i] = i;
            p.push_back(i);
        }
        for (int j = 0; i * p[j] <= N; ++j) {
            lpf[i * p[j]] = p[j];
            if (p[j] == lpf[i]) {
                break;
            }
        }
    }
    
    int t;
    cin >> t;
    while(t-- > 0){
        int l, r;
        cin >> l >> r;
        int diff = r - l;
        if(diff == 1){
            cout << "-1\n";
            continue;
        }
        int ans = (int) 1e9;
        while(diff != 1){
            int factor = lpf[diff];
            int distToNext = l % factor;
            int chainLen = factor - (distToNext == 0? factor : distToNext);
            ans = min(ans, chainLen);
            diff /= factor;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
