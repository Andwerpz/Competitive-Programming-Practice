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

//AtCoder - AGC37C

//Intuitively, it's pretty hard to figure out a sequence of operations that will get us from A -> B, so 
//instead let's consider some sequence of inverse operations that can get us from B -> A. If we just
//reverse the operations performed, then we can derive a valid sequence to get from A -> B. 

//Our inverse operation will be picking three consecutive elements, a, b, c, and then setting b = b - (a + c).
//Note that in order to actually apply this operation, (b - b_orig) > a + c, as the resulting value of b cannot
//go under b_orig, which is the original element corresponding to b in A. 

//Observe that actually no matter how we apply these inverse operations, the resulting array will not change 
//after applying all that we can. Actually we can also prove that the number of operations will be minimized. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vl a(n), b(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    for(int i = 0; i < n; i++){
        cin >> b[i];
    }
    queue<int> q;
    for(int i = 0; i < n; i++){
        if(b[i] > b[(i + n - 1) % n] + b[(i + 1) % n]) {
            q.push(i);
        }
    }
    ll ans = 0;
    while(q.size() != 0){
        int cur = q.front();
        q.pop();
        ll amt = b[(cur + n - 1) % n] + b[(cur + 1) % n];
        ll mult = (b[cur] - a[cur]) / amt;
        ans += mult, b[cur] -= mult * amt;
        int l = (cur + n - 1) % n, r = (cur + 1) % n;
        if(b[l] > b[(l + n - 1) % n] + b[(l + 1) % n]) q.push(l);
        if(b[r] > b[(r + n - 1) % n] + b[(r + 1) % n]) q.push(r);
    }
    bool is_valid = true;
    for(int i = 0; i < n; i++){
        if(a[i] != b[i]) is_valid = false;
    }
    cout << (is_valid? ans : -1) << "\n";
    
    return 0;
}