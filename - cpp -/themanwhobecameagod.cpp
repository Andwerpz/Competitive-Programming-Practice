#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1847A

//there are n - 1 differences, and you can remove k of them. What is the minimum sum if you choose the k to remove?

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        for(int i = 0; i < n; i++) {
            cin >> a[i];
        }
        vector<int> d(n - 1);
        int ans = 0;
        for(int i = 0; i < n - 1; i++){
            d[i] = abs(a[i] - a[i + 1]);
            ans += d[i];
        }
        sort(d.begin(), d.end());
        for(int i = n - 2; i >= n - k; i--){
            ans -= d[i];
        }
        cout << ans << "\n";
    }
    
    return 0;
}
