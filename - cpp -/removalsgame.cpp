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

//Codeforces - 2002B

//note that it's very hard for bob to win. If alice ever removes an element that bob can't immediately remove, 
//then bob is forced to remove some other element. This means that alice can then ignore bob and remove all other elements
//except for the one that bob removed, guaranteeing her win. 

//this means that bob can only win if p = q, or p = reverse(q). 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vi a(n), b(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        for(int i = 0; i < n; i++){
            cin >> b[i];
        }
        bool bobwin = false;
        bobwin = bobwin || (a == b);
        reverse(a.begin(), a.end());
        bobwin = bobwin || (a == b);
        cout << (bobwin? "Bob" : "Alice") << "\n";
    }
    
    return 0;
}