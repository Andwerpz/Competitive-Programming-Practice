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

//AtCoder - ARC138D

//first, construct a xor basis where every element in the basis has popcount = k. 
//then, construct gray code of size n. We'll then relate every bit in the gray code to one basis
//element. We can then construct the permutation using the gray code as a marker for
//which basis elements to include in every element of the permutation. 

//this creates a permutation because we've constructed a basis of size n, and iterating through
//every combination of the basis vectors should span the set. 

vi gen_code(int n) {
    if(n == 0) return {0};
    vi a = gen_code(n - 1);
    vi ans(1 << n);
    for(int i = 0; i < a.size(); i++){
        ans[i] = a[i];
    }
    for(int i = 0; i < a.size(); i++){
        ans[i + a.size()] = a[a.size() - 1 - i] ^ (1 << (n - 1));
    }
    return ans;
}

bool insertBasis(vector<int>& basis, int x){
    for(int i = 0; i < basis.size(); i++){
        if((x & 1 << i) == 0) continue;
        if(!basis[i]) {basis[i] = x; return true;}
        x ^= basis[i];
    }
    return false;
}

bool inBasis(vector<int>& basis, int x){
    for(int i = 0; i < basis.size(); i++)
        if(x & 1 << i) x ^= basis[i];
    return x == 0;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    if((k != 1 && k == n) || k % 2 == 0) {
        cout << "No\n";
        return 0;
    }
    vi a = gen_code(n);
    vi b(n), b0(n, 0);
    //construct basis
    for(int i = 0; i < n; i++){
        for(int j = 1; j < (1 << n); j++){
            if(__builtin_popcount(j) != k) continue;
            if(!inBasis(b0, j)) {
                insertBasis(b0, j);
                b[i] = j;
                break;
            }
        }
    }
    //construct sequence
    cout << "Yes\n";
    for(int i = 0; i < (1 << n); i++){
        int cur = 0;
        for(int j = 0; j < n; j++){
            if(a[i] & (1 << j)) cur ^= b[j];
        }
        cout << cur << " ";
    }
    cout << "\n";
    
    return 0;
}