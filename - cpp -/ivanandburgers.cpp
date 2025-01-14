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

//Codeforces - 1100F

//for each left point, store the closest 20 elements to the right that increase the span of the xor basis. 
//we can precompute this in O(n * B^2).

//then to answer queries, we can construct the xor basis for each subarray in O(B^2) time, and then just
//construct the max element. 

const int B = 20;
bool basisInsert(vector<int>& b, int x){
    for(int i = B - 1; i >= 0; i--){
        if((x & (1 << i)) == 0) continue;
        if(!b[i]) {b[i] = x; return true;}
        x ^= b[i];
    }
    return false;
}

bool inBasis(vector<int>& b, int x){
    for(int i = B - 1; i >= 0; i--)
        if(x & (1 << i)) x ^= b[i];
    return x == 0;
}

int basisMax(vector<int>& b) {
    int ans = 0;
    for(int i = B - 1; i >= 0; i--) if(b[i] && !(ans & (1 << i))) ans ^= b[i];
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vi a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    vvi b(n);
    for(int i = n - 1; i >= 0; i--){
        vi ba(B, 0);
        basisInsert(ba, a[i]);
        b[i].push_back(i);
        if(i != n - 1) for(int j = 0; j < b[i + 1].size(); j++) if(basisInsert(ba, a[b[i + 1][j]])) b[i].push_back(b[i + 1][j]);
    }
    int q;
    cin >> q;
    for(int i = 0; i < q; i++){
        int l, r;
        cin >> l >> r;
        l --;
        vi ba(B, 0);
        for(int x : b[l]) if(x < r) basisInsert(ba, a[x]);
        cout << basisMax(ba) << "\n";
    }
    
    return 0;
}