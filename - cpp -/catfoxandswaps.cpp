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

//Codeforces - 1973E

//given some (l, r) pair, identify all the pairs of values that we can sort. If we represent this as 
//an undirected graph, with each value being a node, and edges being whether or not we can swap the pair
//given (l, r), I claim there will be at most 1 component of size > 1. 

//then, within each component, we can arbitrarily rearrange all values within the component. Furthermore, 
//the component of size > 1 will either represent a prefix or suffix of the values. 

//bruh, this is too caseworky. Just like look at editorial or smth. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        ll n;
        cin >> n;
        vi a(n + 1), b(n + 1);  //a[ind] = val, b[val] = ind
        bool sorted = true;
        for(int i = 1; i <= n; i++){
            cin >> a[i];
            b[a[i]] = i;
            if(a[i] != i) sorted = false;
        }
        if(sorted) {    //any pair works
            cout << (n * 2) * (n * 2 + 1) / 2 << "\n";
            continue;
        }
        ll ans = 0;
        //these ranges can just sort the entire array
        ans += (n + 1) * n - 1; //l <= n + 1 && r >= n + 1 and l != r
        //l < r
        for(int l = n + 2; l <= 2 * n; l++){ //sort suffix
            if(a[l - n - 1] != l - n - 1) break;
            ans += (2 * n) - l;
        }
        for(int r = n; r >= 1; r--) {   //sort prefix
            if(a[r] != r) break;
            ans += r - 1;
        }
        //l == r
        set<int> s;
        for(int i = 1; i <= n; i++){
            if(a[i] == i) continue;
            s.insert(a[i] + i);
        }
        ans += s.size() == 1;
        cout << ans << "\n";
    }
    
    return 0;
}