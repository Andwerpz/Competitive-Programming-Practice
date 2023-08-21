#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1832E

//as the title suggests, this is a combinatorics problem. 

//lets try computing elements of the 'b' array without the mod operator at the end. 
//in the case where k = 1, then:
//b[1] = 1 * a[1]
//b[2] = 2 * a[1] + 1 * a[2]
//b[3] = 3 * a[1] + 2 * a[2] + 1 * a[3]. 

//and if k = 2, then:
//b[1] = 0
//b[2] = 1 * a[1]
//b[3] = 3 * a[1] + 1 * a[2]
//b[4] = 6 * a[1] + 3 * a[2] + 1 * a[3]

//denote b[i][j] as the value of b[i] when k = j. 
//we can argue that b[i][j] = sum(b[0][j - 1], b[1][j - 1], ... b[i - 1][j - 1]). 

//in actuality, the coefficients for each a[i], if k is held constant, follow the same diagonal on pascal's triangle.
//(the reason for this is because the binomial expansion values are all on pascal's triangle.)
//Since we can compute pascal's triangle with prefix sums due to its structure, we can easily compute b[i][j] using prefix sums. 

//Pascal's triangle for reference:
//1
//1 1
//1 2 1
//1 3 3 1
//1 4 6 4 1

//since k is so small, (k <= 5), we just compute the original 'a' array, then prefix sum it k + 1 times to get the 'b' array. 
//from there, computing the answer is trivial. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll mod = 998244353;
    ll n, a, x, y, m, k;
    cin >> n >> a >> x >> y >> m >> k;
    vector<ll> b(n, 0);
    for(int i = k - 1; i < n; i++){
        b[i] = a;
        a *= x;
        a += y;
        a %= m;
    }
    for(int i = 0; i <= k; i++){
        for(int j = 1; j < n; j++){
            b[j] += b[j - 1];
            if(b[j] >= mod){
                b[j] -= mod;
            }
        }
    }
    ll ans = 0;
    for(int i = 0; i < n; i++){
        ll coeff = i + 1;
        ll c = b[i] * coeff;
        ans ^= c;
    }
    cout << ans << "\n";
    
    return 0;
}
