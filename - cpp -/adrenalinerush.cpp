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

//2024-2025 ICPC NERC - A

//consider moving the cars in order from first to last car in the final ordering. 
//move every car to the back, and then to their final ordering. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vi a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
        a[i] --;
    }
    vector<pii> ans;
    vi b(n);
    for(int i = 0; i < n; i++){
        b[i] = i;
    }
    for(int i = 0; i < n; i++){
        int ind = -1;
        for(int j = 0; j < n; j++){
            if(b[j] == a[i]) {
                ind = j; break;
            }
        }
        for(int j = ind; j < n - 1; j++){
            ans.push_back({b[j + 1], b[j]});
            swap(b[j], b[j + 1]);
        }
        for(int j = n - 2; j >= i; j--){
            ans.push_back({b[j + 1], b[j]});
            swap(b[j], b[j + 1]);
        }
    }
    cout << ans.size() << "\n";
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i].first + 1 << " " << ans[i].second + 1 << "\n";
    }
    
    return 0;
}