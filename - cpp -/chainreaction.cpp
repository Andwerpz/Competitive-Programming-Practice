#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1954E

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> a(n);
    int amax = 0;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        amax = max(amax, a[i]);
    }
    vector<vector<int>> b(amax + 1, vector<int>(0));
    for(int i = 0; i < n; i++){
        b[a[i]].push_back(i);
    }
    vector<int> d(amax + 1, -1);
    int dcnt = 0;
    vector<bool> v(n, false);
    for(int i = amax; i >= 1; i--){
        for(int j = 0; j < b[i].size(); j++){
            int ind = b[i][j];
            v[ind] = true;
            dcnt ++;
            if(ind != 0 && v[ind - 1]) {
                dcnt --;
            }
            if(ind != n - 1 && v[ind + 1]) {
                dcnt --;
            }
        }
        d[i] = dcnt;
    }
    for(int i = 1; i <= amax; i++){
        ll ans = 0;
        for(int j = 0; j * i + 1 <= amax; j++){
            ans += d[j * i + 1];
        }
        cout << ans << " ";
    }
    cout << "\n";
    
    return 0;
}
