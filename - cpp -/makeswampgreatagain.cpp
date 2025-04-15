#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

//The 3rd Universal Cup. Stage 18: Southeastern Europe - J

//for some t[i], the lower bound on the amount of operations required for it is n - f(t[i]), where f(x) is the number of 
//occurrences of x in a. However, observe that there are some t[i] that take 2 operations to convert the first element. 
//So, just account for that when computing the answer. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n;
    cin >> n;
    vi a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vi occ(1e5 + 100, 0);
    vector<bool> f(1e5 + 100, false);
    for(int i = 0; i < n; i++){
        int u = a[i], v = a[(i + 1) % n], w = a[(i + 2) % n];
        f[min({u, v, w})] = true;
        f[max({u, v, w})] = true;
    }
    for(int i = 0; i < n; i++) occ[a[i]] ++;
    for(int i = 0; i < n; i++){
        int ans = n - occ[a[i]];
        if(!f[a[i]]) ans ++;
        cout << ans << " ";
    }
    cout << "\n";

    return 0;
}