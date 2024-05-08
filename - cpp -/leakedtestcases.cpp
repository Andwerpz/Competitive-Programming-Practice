#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//ACPC 2024 Spring Contest - L

//i came up with this whole linear algebra solution D:

//we can treat each segment as a vector in R^m. Each element of the array is an elementary basis for R^m, and our goal
//is to find the 'length' of each of the elementary basis vectors. 

//To do this, we want to determine if the set of vectors we are given can form a basis for R^m. If the can, we can uniquely
//determine each of the elements in the array. 

//To find the basis, we first say that each basis vector has to "start" from a different point in the array compared to
//any other basis vector. This guarantees that every basis vector is linearly independent. Sort all the vectors by
//increasing end point, and try to add each of them to the basis. If there is already a basis vector at the current
//vector's starting location, then we can subtract that basis vector from the current vector and try again. 
//to generate the basis in linear time, we can use path compression similar to the one in DSU. 

template <typename T>
struct Segtree {
    //note that t[0] is not used
    int n;
    T* t;
    T uneut, qneut;

    //single element modification function
    function<T(T, T)> fmodify;

    //product of two elements for query and updating tree
    function<T(T, T)> fcombine;

    Segtree(int n, T updateNeutral, T queryNeutral, function<T(T, T)> fmodify, function<T(T, T)> fcombine) {
        this -> n = n;
        t = new T[2 * n];

        this -> fmodify = fmodify;
        this -> fcombine = fcombine;

        uneut = updateNeutral;
        qneut = queryNeutral;

        for(int i = 0; i < n; i++){
            t[i + n] = uneut;
        }
        build();
    }

    void build() { // build the tree after manually assigning the values.
        for (int i = n - 1; i > 0; i--) {   
            t[i] = fcombine(t[i * 2], t[i * 2 + 1]);
        }
    }

    void modify(int p, T value) { // set value at position p
        p += n;
        t[p] = fmodify(t[p], value);
        for (p /= 2; p > 0; p /= 2) {
            t[p] = fcombine(t[p * 2], t[p * 2 + 1]);
        }
    }

    T query(int l, int r) { // sum on interval [l, r)
        T l_res = qneut, r_res = qneut;
        bool l_none = true, r_none = true;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l % 2 == 1) {
                if(l_none) {
                    l_none = false;
                    l_res = t[l];
                }
                else {
                    l_res = fcombine(l_res, t[l]);
                }
                l++;
            }
            if (r % 2 == 1) {
                r--;
                if(r_none) {
                    r_none = false;
                    r_res = t[r];
                }
                else {
                    r_res = fcombine(t[r], r_res);
                }
            }
        }
        if(l_none) {
            return r_res;
        }
        if(r_none) {
            return l_res;
        }
        return fcombine(l_res, r_res);
    }

    T query(int ind) {
        return this->query(ind, ind + 1);
    }
};

void push_to_end(vector<pair<int, ll>>& basis, int ind) {
    // cout << "PUSH : " << ind << "\n";
    int r = basis[ind].first;
    if(r == basis.size() || basis[r].first == -1){
        return;
    }
    push_to_end(basis, r);
    basis[ind].first = basis[r].first;
    basis[ind].second += basis[r].second;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<pair<pair<int, int>, int>> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i].first.first >> a[i].first.second >> a[i].second;
        a[i].first.first --;
    }
    //find basis
    //ascending by end point
    sort(a.begin(), a.end(), [](pair<pair<int, int>, int>& a, pair<pair<int, int>, int>& b) -> bool {
        return a.first.second < b.first.second;
    });
    vector<pair<int, ll>> basis(m, {-1, -1});    //{end, val}
    for(int i = 0; i < n; i++){
        int l = a[i].first.first;
        int r = a[i].first.second;
        ll x = a[i].second;
        // cout << "TRY BASIS : " << l << " " << r << " " << x << "\n";
        while(l != r){
            if(basis[l].first == -1){
                basis[l].first = r;
                basis[l].second = x;
                // cout << "SET BASIS : " << l << " " << r << " " << x << "\n";
                break;
            }
            push_to_end(basis, l);
            x -= basis[l].second;
            l = basis[l].first;
        }
    }
    bool inf_sol = false;
    for(int i = 0; i < m; i++){
        if(basis[i].first == -1){
            inf_sol = true;
            basis[i].first = m;
            basis[i].second = 0;
        }
        // cout << "BEFORE PUSH : " << basis[i].first << " " << basis[i].second << endl;
    }
    for(int i = 0; i < m; i++){
        push_to_end(basis, i);
        // cout << "END BASIS : " << basis[i].first << " " << basis[i].second << "\n";
    }
    vector<ll> sol(m);
    for(int i = 0; i < m; i++){
        sol[i] = basis[i].second;
        if(i != m - 1){
            sol[i] -= basis[i + 1].second;
        }
    }
    function<ll(ll, ll)> fmodify = [](const ll src, const ll val) -> ll{return src + val;};
    function<ll(ll, ll)> fcombine = [](const ll a, const ll b) -> ll{return a + b;};
    Segtree<ll> segt(m, 0, 0, fmodify, fcombine); 
    for(int i = 0; i < m; i++){
        segt.modify(i, sol[i]);
    }
    bool is_valid = true;
    for(int i = 0; i < n; i++){
        int l = a[i].first.first;
        int r = a[i].first.second;
        ll x = a[i].second;
        if(segt.query(l, r) != x){
            is_valid = false;
        }
    }
    if(!is_valid) {
        cout << "we bad at math too\n";
    }
    else {
        if(inf_sol) {
            cout << "at least we can do math\n";
        }
        else {
            for(int i = 0; i < m; i++){
                cout << sol[i] << " ";
            }
            cout << "\n";
        }
    }

    
    return 0;
}
