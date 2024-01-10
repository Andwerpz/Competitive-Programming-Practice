#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1916E

//i'll refer to the activities as colors. 
//the problem boils down to efficiently finding paths with the most distinct colors. The technique
//used here could be applied anytime this shows up. 

//If for each node, we compute the maximum answer if it were the LCA, then we can just take the max
//out of all of them and that's the answer to the problem. 

//to do this, we can maintain an array and do a DFS from the root such that if we are currently at
//node i, and node j is in the subtree of node i, we know the number of distinct colors on the path
//from j to i. 

//let's build a segment tree over the euler tour of the tree, supporting range increment and range maximum
//queries. This will be our array keeping track of number of distinct colors on paths. For each node, after
//computing the answer for all our children, the segment tree will be valid for all of our subtrees. 
//The only node that isn't considered is the current node. In the case that the current color doesn't occur
//in the subtree, we can just add 1 to the entire subtree, but if it does occur, then we're overcounting
//by doing this. 

//to fix the overcounting, we can notice that we only overcount in the subtrees who's roots are the same color
//as the current node. However, not all roots that are the same color are overcounted, only ones that if you 
//consider the shortest path between them and the current node, no other nodes of the shared color are present. 
//Thus, for each node, we can keep track of all such children that satisfy this property, and add -1 to each
//of their subtrees. We can precompute this in linear time. 

//finally, for each child of the current node, find the maximum path length, and multiply the two longest ones. 

void calc_near(int cur, vector<vector<int>>& c, vector<int>& a, vector<int>& a_near, vector<int>& near) {
    int cur_near = a_near[a[cur]];
    a_near[a[cur]] = cur;
    near[cur] = cur_near;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        calc_near(next, c, a, a_near, near);
    }
    a_near[a[cur]] = cur_near;
}

void euler_tour(int cur, vector<vector<int>>& c, int& cnt, vector<int>& lo, vector<int>& ro) {
    lo[cur] = cnt;
    cnt ++;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        euler_tour(next, c, cnt, lo, ro);
        cnt ++;
    }
    ro[cur] = cnt;
}

template <typename T>
struct SegtreeLazy {
    public:
        int n;
        T* t;    //stores product of range
        T* d;    //lazy tree
        bool* upd;  //marks whether or not a lazy change is here
        T uneut, qneut;

        //single element modify
        function<T(T, T)> fmodify;

        //k element modify
        function<T(T, T, int)> fmodifyk;

        //product of two elements for query
        function<T(T, T)> fcombine;

        SegtreeLazy(int maxSize, T updateNeutral, T queryNeutral, function<T(T, T)> fmodify, function<T(T, T, int)> fmodifyk, function<T(T, T)> fcombine) {
            n = maxSize;
            uneut = updateNeutral;
            qneut = queryNeutral;

            this -> fmodify = fmodify;
            this -> fmodifyk = fmodifyk;
            this -> fcombine = fcombine;

            //raise n to nearest pow 2
            int x = 1;
            while(x < n) {
                x <<= 1;
            }
            n = x;

            t = new T[n * 2];
            d = new T[n * 2];
            upd = new bool[n * 2];

            //make sure to initialize values
            for(int i = 0; i < n * 2; i++){
                t[i] = uneut;
            }
            for(int i = 0; i < n * 2; i++){
                d[i] = uneut;
                upd[i] = false;
            }
        }

        void modify(int l, int r, T val) {    //modifies the range [l, r)
            _modify(l, r, val, 0, n, 1);
        }

        void modify(int ind, T val) { //modifies the range [ind, ind + 1)
            _modify(ind, ind + 1, val, 0, n, 1);
        }

        T query(int l, int r) {   //queries the range [l, r)
            return _query(l, r, 0, n, 1);
        }

        T query(int ind) {    //queries the range [ind, ind + 1)
            return _query(ind, ind + 1, 0, n, 1);
        }

    private:
        //calculates value of node based off of children
        //k is the amount of values that this node represents. 
        void combine(int ind, int k) {
            if(ind >= n){
                return;
            }
            int l = ind * 2;
            int r = ind * 2 + 1;
            //make sure children are correct value before calculating
            push(l, k / 2);
            push(r, k / 2);
            t[ind] = fcombine(t[l], t[r]);
        }

        //registers a lazy change llo this node
        void apply(int ind, T val) {
            upd[ind] = true;
            d[ind] = fmodify(d[ind], val);
        }

        //applies lazy change to this node
        //k is the amount of values that this node represents. 
        void push(int ind, int k) {
            if(!upd[ind]) {
                return;
            }
            t[ind] = fmodifyk(t[ind], d[ind], k);
            if(ind < n) {
                int l = ind * 2;
                int r = ind * 2 + 1;
                apply(l, d[ind]);
                apply(r, d[ind]);
            }
            upd[ind] = false;
            d[ind] = uneut;
        }

        void _modify(int l, int r, T val, int tl, int tr, int ind) {
            if(l == r){
                return;
            }
            if(upd[ind]) {
                push(ind, tr - tl);
            }
            if(l == tl && r == tr) {
                apply(ind, val);
                push(ind, tr - tl);
                return;
            }
            int mid = tl + (tr - tl) / 2;
            if(l < mid) {
                _modify(l, min(r, mid), val, tl, mid, ind * 2);
            }
            if(r > mid) {
                _modify(max(l, mid), r, val, mid, tr, ind * 2 + 1);
            }
            combine(ind, tr - tl);
        }

        T _query(int l, int r, int tl, int tr, int ind) {
            if(l == r){
                return qneut;
            }  
            if(upd[ind]) {
                push(ind, tr - tl);
            }
            if(l == tl && r == tr){
                return t[ind];
            }
            int mid = tl + (tr - tl) / 2;
            T lans = qneut;
            T rans = qneut;
            if(l < mid) {
                lans = _query(l, min(r, mid), tl, mid, ind * 2);
            }
            if(r > mid) {
                rans = _query(max(l, mid), r, mid, tr, ind * 2 + 1);
            }
            return fcombine(lans, rans);
        }
};

ll calc_ans(int cur, vector<vector<int>>& c, SegtreeLazy<int>& segt, vector<vector<int>>& c_list, vector<int>& lo, vector<int>& ro) {
    ll ans = 0;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        ans = max(ans, calc_ans(next, c, segt, c_list, lo, ro));
    }
    //update segt
    segt.modify(lo[cur], ro[cur], 1);
    for(int i = 0; i < c_list[cur].size(); i++){
        int next = c_list[cur][i];
        segt.modify(lo[next], ro[next], -1);
    }
    //find best ans with cur as lca
    vector<ll> paths(0);
    paths.push_back(1);
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        paths.push_back(segt.query(lo[next], ro[next]));
    }
    sort(paths.begin(), paths.end());
    reverse(paths.begin(), paths.end());
    ans = max(ans, paths[0]);
    if(paths.size() >= 2){
        ans = max(ans, paths[0] * paths[1]);
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<vector<int>> c(n, vector<int>(0));
        for(int i = 1; i < n; i++){
            int p;
            cin >> p;
            p --;
            c[p].push_back(i);
        }
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
            a[i] --;
        }
        vector<int> a_near(n, -1);
        vector<int> near(n, -1);    //for each node, what is the closest ancestor that shares my color?
        calc_near(0, c, a, a_near, near);
        vector<vector<int>> c_list(n, vector<int>(0));  //for each node, what children have me as their closest color ancestor?
        for(int i = 0; i < n; i++){
            if(near[i] == -1){
                continue;
            }
            c_list[near[i]].push_back(i);
        }
        vector<int> lo(n), ro(n);   //left and right occurrences of each node in the euler tour
        int tour_size = 0;
        euler_tour(0, c, tour_size, lo, ro);
        function<int(int, int)> fmodify = [](const int src, const int val) -> int{return src + val;};
        function<int(int, int, int)> fmodifyk = [](const int src, const int val, const int k) -> int{return src + val;};
        function<int(int, int)> fcombine = [](const int a, const int b) -> int{return max(a, b);};
        SegtreeLazy<int> segt(tour_size, 0, -1e9, fmodify, fmodifyk, fcombine); //increment modify, maximum query
        ll ans = calc_ans(0, c, segt, c_list, lo, ro);
        cout << ans << "\n";
    }
    
    return 0;
}
