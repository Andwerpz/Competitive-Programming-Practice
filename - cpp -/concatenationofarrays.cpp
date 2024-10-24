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

//Codeforces - 2023A

//can prove that it's optimal to sort the pairs by their sum. Read editorial for proof. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<pii> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i].first >> a[i].second;
        }
        sort(a.begin(), a.end(), [](pii a, pii b) -> bool{
            if(min(a.first, a.second) != min(b.first, b.second)) {
                return min(a.first, a.second) < min(b.first, b.second);
            }
            return max(a.first, a.second) < max(b.first, b.second);
        });
        for(int i = 0; i < n; i++){
            cout << a[i].first << " " << a[i].second << " ";
        }
        cout << "\n";
    }
    
    return 0;
}