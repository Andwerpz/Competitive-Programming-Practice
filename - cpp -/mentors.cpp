#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

typedef pair<int,int> pii;
typedef vector<int> vi;
#define rep(i, a ,b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define z(s) (int) (x).size()

//SWERC 2020 - F

int c[2022][2022];

/*
2 4 1000


*/

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int r, n, m; cin >> r >> n >> m;

    // if(r == n) {
    //     cout << ((int) (n == 1)) % m << '\n';
    //     return 0;
    // }

    for(int i = 0; i <= 2021; i++) {
        for(int j = 0; j <= i; j++) {
            if(j == 0) {
                c[i][j] = 1 % m;
            } else {
                c[i][j] = (c[i-1][j] + c[i-1][j-1]) % m;
            }
        }
    }

    vector<int> a(n + 1); //a[i] => number of subtrees with i nodes that can be mapped to a permutation. 
    a[0] = 1 % m;
    a[1] = 1 % m;
    for(int i = 2; i <= n; i++) {
        for(int k = 1; k <= i - 1; k++) {
            //fix one subtree to have element i - 1 in it. Then the number of ways is choose(n - 2, k - 1) * a[k] * a[n - k - 1]. 
            a[i] = (a[i] + 1LL * a[k] * c[i - 2][k - 1] % m * a[i - 1 - k]) % m;
        }
    }

    // for(int i = 0; i <= n; i++) {
    //     cout << "i : " << i << " a[i] : " << a[i] << '\n';
    // }

    //now given our fixed R, we can do some things
    vector<vector<int>> dp(n + 1, vector<int>(n + 1));
    for(int i = n - r + 1; i <= n; i++) {
        int k = i - (n - r);
        int sub = 0;
        for(int j = 2; j <= k; j++) {
            sub = (sub + 1LL * dp[i - j + 1][k - j + 1] % m * c[k - 1][j - 1] % m * a[j]) % m;
        }
        dp[i][k] = (a[i] - sub + m) % m;
    }

    cout << dp[n][r] << '\n';


    // vector<int> dp(r + 1); //dp[i] = dp[]
    // dp[0] = 
    // for(int k = 1; k <= r; k++) {
    //     int N = k + (n - r);
    //     int sub = 0;
    //     for(int i = 2; i <= k; i++) {
    //         sub = (sub + 1LL * dp[k - i + 1] * c[k - 1][i - 1]) % m;
    //     }
    //     dp[k] = (a[N] - sub + m) % m;
    // }

    // cout << dp[r] << '\n';

    return 0;
}


// #include<bits/stdc++.h>
// using namespace std;
// typedef long long ll;
// typedef long double ld;

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(0), cout.tie(0);

//     int r, n, m; cin >> r >> n >> m;
//     vector<ll> dp(n + 1);
//     dp[0] = 1;
//     for (int i = n - 1; i >= 1; i--) {
//         int s = n - i;
//         cout << "processing " << i << " " << s << '\n';
//         vector<ll> ndp(n + 1);
//         if (i < r) s--;
//         for (int k = 0; k <= s; k++) {
//             if (k < s && k + 1 < s) {
//                 ndp[k] = dp[k + 1] * (k + 1) % m;
//             }

//             if (k > 0) {
//                 assert(ndp[k] >= 0);
//                 ndp[k] = (ndp[k] + dp[k - 1] * (s - k + 1)) % m;
//                 // cout << dp[k - 1] << " " << s << " " << s - k + 1 << " " << dp[k - 1] * (s - k + 1) << '\n';
//             }
//         }

//         ll ans = 0;
//         for (ll x: ndp) cout << x << " ";
//         cout << '\n';

//         swap(dp, ndp);
//     }

//     ll ans = 0;
//     for (ll x: dp) cout << x << " ";
//     cout << '\n';

//     cout << (ans % m + m) % m << '\n';

//     return 0;
// }
