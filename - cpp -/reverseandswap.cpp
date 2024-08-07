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

//Codeforces - 1401F

//when reading the problem, it becomes pretty obvious that some sort of modified segment tree will just solve
//it outright. 

//Let's take stock of what our segment tree needs to support:
//1. assignment modify
//2. 'swap' operation. 
//3. range sum query

//note that we don't have to explicitly support the reverse operation, as reverse(k) is equivalent to
//swap(0) + swap(1) + ... + swap(k - 1). 

//let's represent our segment tree as a full binary tree. Note that all the swap(k) operation does is
//takes all nodes of depth n - k - 1, and swaps their left and right children. But we don't have to 
//actually go through and swap all the children, we just have to keep track for every layer, whether
//or not it's swapped. When we're doing assignment modify or range query, we can account for these
//layer swaps. 

vl a;
int n, b;
vb sw;

void modify(int ind, int val) {
    int rind = 0;
    for(int i = 0; i < b; i++){
        if(((ind >> i) & 1) != 0 ^ sw[i]) {
            rind += 1 << i;
        }
    }
    rind += n;
    a[rind] = val;
    for(int i = rind / 2; i != 0; i /= 2){
        a[i] = a[i * 2] + a[i * 2 + 1];
    }
}

ll query(int l, int r, int tl = 0, int tr = n, int tind = 1, int bit = b - 1) {
    if(l >= r){
        return 0;
    }
    if(l == tl && r == tr) {
        return a[tind];
    }
    int mid = tl + (tr - tl) / 2;
    int al = min(l, mid);
    int ar = min(r, mid);
    int bl = max(l, mid);
    int br = max(r, mid);
    if(sw[bit]) {
        int range = (tr - tl) / 2;
        swap(al, bl);
        swap(ar, br);
        al -= range;
        ar -= range;
        bl += range;
        br += range;
    }
    return query(al, ar, tl, mid, tind * 2, bit - 1) + query(bl, br, mid, tr, tind * 2 + 1, bit - 1);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int q;
    cin >> b >> q;
    n = 1 << b;
    a = vl(n * 2, 0);
    for(int i = n; i < n * 2; i++){
        cin >> a[i];
    }
    for(int i = n - 1; i > 0; i--){
        a[i] = a[i * 2] + a[i * 2 + 1];
    }
    sw = vb(b, false);
    for(int i = 0; i < q; i++){
        int type;
        cin >> type;
        if(type == 1){
            int x, k;
            cin >> x >> k;
            x --;
            modify(x, k);
        }
        else if(type == 2){
            int k;
            cin >> k;
            for(int j = 0; j < k; j++){
                sw[j] = !sw[j];
            }
        }
        else if(type == 3){
            int k;
            cin >> k;
            sw[k] = !sw[k];
        }
        else if(type == 4){
            int l, r;
            cin >> l >> r;
            l --;
            cout << query(l, r) << "\n";
        }
    }
    
    return 0;
}