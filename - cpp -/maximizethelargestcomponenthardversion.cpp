#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1985H2

//consider how to solve the problem if we only can do the operation on one column. We can first record the range that
//each component occupies with respect to the columns, and increment each component along their range by the amount
//of elements in the component. Filling in a column will not only connect all components in that column, but in adjacent
//columns as well, so we can extend all ranges to the left and right by one to account for this. Finally, we also need
//to account for the cells added when filling in the range, so we can keep track for each column how many empty
//cells there are. 

//Now, fix our row operation at some row i, and solve the same problem above. If we want to change what row we're doing 
//the operation on, we can use a segment tree to do it in amortized log(n) time. 

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

        SegtreeLazy(int maxSize, T updateNeutral, T queryNeutral, T initVal, function<T(T, T)> fmodify, function<T(T, T, int)> fmodifyk, function<T(T, T)> fcombine) {
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
            for(int i = 0; i < n; i++){
                t[i + n] = initVal;
            }
            build();
        }

        void assign(vector<T>& arr) {
            for(int i = 0; i < min(n, (int) arr.size()); i++){
                t[i + n] = arr[i];
            }
            build();
        }

        //build tree after manually assigning values
        void build() {
            for(int i = n - 1; i > 0; i--){
                t[i] = fcombine(t[i * 2], t[i * 2 + 1]);
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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        vector<string> g(n);
        for(int i = 0; i < n; i++){
            cin >> g[i];
        }
        vector<vector<int>> cmp(n, vector<int>(m, -1));
        int nr_cmp = 0;
        vector<int> dr = {-1, 1, 0, 0};
        vector<int> dc = {0, 0, -1, 1};
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(g[i][j] == '.' || cmp[i][j] != -1){
                    continue;
                }
                cmp[i][j] = nr_cmp;
                queue<pair<int, int>> q;
                q.push({i, j});
                while(q.size() != 0){
                    int r = q.front().first;
                    int c = q.front().second;
                    q.pop();
                    for(int k = 0; k < 4; k++){
                        int nr = r + dr[k];
                        int nc = c + dc[k];
                        if(nr < 0 || nc < 0 || nr >= n || nc >= m){
                            continue;
                        }
                        if(g[nr][nc] == '.'){
                            continue;
                        }
                        if(cmp[nr][nc] != -1){
                            continue;
                        }
                        cmp[nr][nc] = nr_cmp;
                        q.push({nr, nc});
                    }
                }
                nr_cmp ++;
            }
        }
        vector<pair<int, int>> re(nr_cmp, {1e9, -1e9}), ce(nr_cmp, {1e9, -1e9});
        vector<int> csize(nr_cmp, 0);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(cmp[i][j] == -1){
                    continue;
                }
                int ind = cmp[i][j];
                re[ind].first = min(re[ind].first, i);
                re[ind].second = max(re[ind].second, i);
                ce[ind].first = min(ce[ind].first, j);
                ce[ind].second = max(ce[ind].second, j);
                csize[ind] ++;
            }
        }
        for(int i = 0; i < re.size(); i++){
            re[i].first = max(0, re[i].first - 1);
            re[i].second = min(n, re[i].second + 2);
        }
        for(int i = 0; i < ce.size(); i++){
            ce[i].first = max(0, ce[i].first - 1);
            ce[i].second = min(m, ce[i].second + 2);
        }
        function<int(int, int)> fmodify = [](const int src, const int val) -> int{return src + val;};
        function<int(int, int, int)> fmodifyk = [](const int src, const int val, const int k) -> int{return src + val;};
        function<int(int, int)> fcombine = [](const int a, const int b) -> int{return max(a, b);};
        SegtreeLazy<int> segt(m, 0, -1e9, 0, fmodify, fmodifyk, fcombine);
        for(int i = 0; i < nr_cmp; i++){
            int l = ce[i].first;
            int r = ce[i].second;
            segt.modify(l, r, csize[i]);
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(g[i][j] == '.') {
                    segt.modify(j, 1);
                }
            }
        }
        vector<pair<int, pair<int, int>>> ev(0);
        for(int i = 0; i < nr_cmp; i++){
            int l = re[i].first;
            int r = re[i].second;
            ev.push_back({l, {i, -1}});
            ev.push_back({r, {i, 1}});
        }
        sort(ev.begin(), ev.end());
        vector<int> ra(n, 0);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                ra[i] += g[i][j] == '.';
            }
        }
        int ptr = 0;
        int row_amt = 0;
        int ans = 0;
        for(int i = 0; i < n; i++){
            while(ptr != ev.size() && ev[ptr].first == i) {
                int ind = ev[ptr].second.first;
                int type = ev[ptr].second.second;
                int l = ce[ind].first;
                int r = ce[ind].second;
                segt.modify(l, r, csize[ind] * type);
                row_amt += csize[ind] * type * -1;
                ptr ++;
            }
            for(int j = 0; j < m; j++){
                if(g[i][j] == '.') {
                    segt.modify(j, -1);
                }
            }
            ans = max(ans, row_amt + segt.query(0, m) + ra[i]);
            for(int j = 0; j < m; j++){
                if(g[i][j] == '.') {
                    segt.modify(j, 1);
                }
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}