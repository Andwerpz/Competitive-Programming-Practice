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

//NCPC 2024 - C

//implementation. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    if(n == 2){
        cout << "1\n";
        cout << "2\n";
        return 0;
    }
    if(n == 3){
        cout << "1\n";
        cout << "3\n";
        return 0;
    }
    vi ans(0);
    if(n % 2 == 1){
        ans.push_back(3);
        n -= 3;
    }
    
    for(int i = 0; i < n / 2; i++){
        ans.push_back(2);
    }
    cout << ans.size() << "\n";
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i] << " ";
    }
    cout << "\n";
    
    return 0;
}