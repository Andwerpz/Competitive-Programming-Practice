#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1913D

//we can simplify the operation to only operate on subarrays of length 2. 
//it can be shown that even with this restriction, it can do anything the old operation can do. 

//we can define a recursive function to solve the problem. 
//f(l, r) = number of reachable arrays from the subarray [l, r). 
//if r - l == 0, the subarray we are considering is empty; return 1. 

//first, we find i, the index of the minimum element.
//next, compute l_ans and r_ans;
//l_ans = f(l, i), r_ans = f(i + 1, r).
//these are the answers to the left and right subarrays relative to the minimum element. 

//next, we can construct the answer. 
//since the left and right subarrays are independent from each other, l_ans * r_ans should be added to the answer. 
//next, if l != 0, it means that at index l - 1, there is a value that is less than everything in [l, r). 
//using that value, we can actually remove the minimum element, so we should add (r_ans - 1) to the answer. 
//likewise if r != n, then add (l_ans - 1). 
//finally, if l != 0 || r != n, then we can add 1 to the answer to account for removing all elements in the subarray. 

template <typename T>
struct Segtree {
    //note that t[0] is not used
    int n;
    T* t;
    int* ind;   //keeps track of the minimum index
    T uneut, qneut;

    //single element modification function
    function<T(T, T)> fmodify;

    //product of two elements for query and updating tree
    function<T(T, T)> fcombine;

    Segtree(int n, T updateNeutral, T queryNeutral, function<T(T, T)> fmodify, function<T(T, T)> fcombine) {
        this -> n = n;
        t = new T[2 * n];
        ind = new int[2 * n];

        this -> fmodify = fmodify;
        this -> fcombine = fcombine;

        uneut = updateNeutral;
        qneut = queryNeutral;

        for(int i = 0; i < 2 * n; i++){
            t[i] = uneut;
        }
    }

    void build() { // build the tree after manually assigning the values.
        for(int i = 0; i < n; i++){
            ind[i + n] = i;
        }

        for (int i = n - 1; i > 0; i--) {   
            t[i] = fcombine(t[i * 2], t[i * 2 + 1]);
            if(t[i * 2] < t[i * 2 + 1]) {
                ind[i] = ind[i * 2];
            }
            else {
                ind[i] = ind[i * 2 + 1];
            }
        }
    }

    int query(int l, int r) { // minimum index of interval [l, r)
        int ind_ans = -1;
        T res = qneut;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l % 2 == 1) {
                if(t[l] < res) {
                    ind_ans = ind[l];
                }
                res = fcombine(res, t[l]);
                l++;
            }
            if (r % 2 == 1) {
                r--;
                if(t[r] < res) {
                    ind_ans = ind[r];
                }
                res = fcombine(res, t[r]);
            }
        }
        return ind_ans;
    }
};

ll mod = 998244353;

ll solve(int n, Segtree<int>& segt, int l, int r) {
    if(r - l == 0){
        return 1;
    }
    int min_ind = segt.query(l, r);
    ll l_ans = solve(n, segt, l, min_ind);
    ll r_ans = solve(n, segt, min_ind + 1, r);
    ll ans = (l_ans * r_ans) % mod;
    if(l != 0){ //remove minimum from left
        ans += r_ans - 1;
    }
    if(r != n){ //remove minimum from right
        ans += l_ans - 1;
    }
    if(l != 0 || r != n) {  //remove everything; can only be done if segment isn't entire array
        ans ++;
    }
    ans %= mod;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        function<int(int, int)> fmodify = [](const int src, const int val) -> int{return val;};
        function<int(int, int)> fcombine = [](const int a, const int b) -> int{return min(a, b);};
        Segtree<int> segt(n, 0, 1e9 + 100, fmodify, fcombine);
        for(int i = 0; i < n; i++){
            int a;
            cin >> a;
            segt.t[i + n] = a;
        }
        segt.build();
        cout << solve(n, segt, 0, n) << "\n";
    }
    
    return 0;
}
