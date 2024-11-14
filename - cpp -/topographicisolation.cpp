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

//Alberta Collegiate Programming Contest 2024, Open Division - H

//monotonic stack. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vi a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    vi ans(n, 1e9);
    {
        stack<pii> s;   //{ind, val}
        for(int i = 0; i < n; i++){
            while(s.size() != 0 && s.top().second < a[i]) {
                s.pop();
            }
            if(s.size() != 0){
                ans[i] = min(ans[i], i - s.top().first);
            }
            s.push({i, a[i]});
        }
    }
    {
        stack<pii> s;
        for(int i = n - 1; i >= 0; i--){
            while(s.size() != 0 && s.top().second < a[i]) {
                s.pop();
            }
            if(s.size() != 0){
                ans[i] = min(ans[i], abs(i - s.top().first));
            }
            s.push({i, a[i]});
        }
    }
    for(int i = 0; i < n; i++){
        if(i == 0 || i == n - 1) {
            cout << "0";
        }
        else if(a[i] > a[i - 1] && a[i] > a[i + 1]){
            cout << (ans[i] == 1e9? -1 : ans[i]);
        }
        else {
            cout << "0";
        }
        cout << " ";
    }
    cout << "\n";
    
    return 0;
}