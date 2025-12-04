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

//Codeforces - 2147A

//if y > x, then we can just do the whole thing in two moves. 

//otherwise y <= x. 
//observe that if x >= y + 2, and y > 1, then you can move 1 on the first move, y on the second, and x - 1 on
//the third. 

//so now, x = y or x = y + 1 or y = 1. 
//observe that if y = 1, then it's always impossible, as it's impossible to move less than 1 on the first move. 
//if x = y, then it's also impossible as after the first move, it's always the case that x != y
//likewise, for x = y + 1, either you move by 1, in which case you have x = y and it's impossible, or you move 
//more than 1, and you have the same issue. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int x, y;
        cin >> x >> y;
        if(y > x) cout << "2\n";
        else if(x - 1 > y && y > 1) cout << "3\n";
        else cout << "-1\n";
    }
    
    return 0;
}