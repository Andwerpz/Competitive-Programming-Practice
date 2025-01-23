#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef array<int, 2> pii;
typedef array<ll, 2> pll;
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

//Codeforces - 2061D

//instead of converting a into b, let's convert b into a. 

//given some number x in b, where could it have come from? If x is even, then it comes from two copies of x / 2, 
//and if x is odd, then it comes from (x - 1) / 2 and (x + 1) / 2. So actually there are no decisions to be made
//when going from b to a. We can just greedily see if the largest element in b corresponds to something in a
//and if it doesn't, just split it into it's two parts and try again. 

//we can keep splitting until the number of elements in b exceeds a. If that happens, it's impossible. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        priority_queue<int> a, b;
        for(int i = 0; i < n; i++){
            int _a;
            cin >> _a;
            a.push(_a);
        }
        for(int i = 0; i < m; i++){
            int _b;
            cin >> _b;
            b.push(_b);
        }
        while(m != 0 && m <= n){
            if(a.top() == b.top()) {
                a.pop(), b.pop(), n --, m --;
                continue;
            }
            if(a.top() > b.top()) break;
            int val = b.top();
            b.pop();
            b.push(val / 2), b.push((val + 1) / 2);
            m ++;
        }
        cout << (n == 0? "YES" : "NO") << "\n";
    }
    
    return 0;
}