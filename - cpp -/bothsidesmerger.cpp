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

//AtCoder - ARC92E

//Observe that you can only merge the value from elements with the same parity. If you designate one parity
//to maximize an element from, then you can effectively 'eliminate' any element of that parity by selecting it
//because we don't care what happens to elements of the opposite parity. 

//Therefore, the strategy is to see which parity is better by just adding up all the positive elements from that
//parity. Building the sequence of moves required is pretty trivial, they even allow you to do it in O(n^2), but
//an O(n) solution exists. One edge case to consider is when all the elements are negative, in which you should
//just pick the maximum negative element, and remove all other elements. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vl a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    ll esum = 0, osum = 0, mx = -1e18, mxind = -1;
    for(int i = 0; i < n; i++){
        if(i % 2) osum += max(0ll, a[i]);
        else esum += max(0ll, a[i]);
        if(a[i] > mx) mx = a[i], mxind = i;
    }
    if(mx <= 0) {
        cout << mx << "\n";
        cout << n - 1 << "\n";
        for(int i = n - 1; i > mxind; i--){
            cout << i + 1 << "\n";
        }
        for(int i = 0; i < mxind; i++){
            cout << "1\n";
        }
        return 0;
    }
    cout << max(esum, osum) << "\n";
    vi op;
    int ptr = 0;
    if(osum > esum) ptr ++, op.push_back(1);
    while(a[ptr] <= 0) ptr += 2, op.push_back(1), op.push_back(1);
    bool leftover = false;
    while(ptr + 2 < n) {
        leftover = false;
        if(a[ptr + 2] <= 0) op.push_back(3), leftover = true;
        else op.push_back(2);
        ptr += 2;
    }
    if(ptr + 1 < n || leftover) op.push_back(2);
    cout << op.size() << "\n";
    for(int x : op) cout << x << "\n";
    
    return 0;
}