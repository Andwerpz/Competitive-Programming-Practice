// #include <bits/stdc++.h>
#include <vector>
#include <iostream>
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

//POJ - 2478

//from F_n to F_{n + 1}, you're literally just adding terms with denominator n + 1 and numerator coprime to n + 1, 
//which is exactly \phi(n). Since we can compute \phi in linear time, this can be solved pretty easily. 

vector<ll> totient;
void calc_totient(int n) {
    totient = vector<ll>(n + 1, 0);
    for (int i = 0; i <= n; i++)
        totient[i] = i;

    for (int i = 2; i <= n; i++) {
        if (totient[i] == i) {
            for (int j = i; j <= n; j += i)
                totient[j] -= totient[j] / i;
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    calc_totient(1e6 + 10);
    vl f(1e6 + 10);
    for(int i = 2; i < f.size(); i++){
        f[i] = f[i - 1] + totient[i];
    }
    int n;
    cin >> n;
    while(n != 0){
        cout << f[n] << "\n";
        cin >> n;
    }
    
    return 0;
}