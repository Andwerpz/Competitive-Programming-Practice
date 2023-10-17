#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;
using pi = pair<int, int>;

//ICPC World Finals 2010 C

struct SegtreeLazy {
    public:
        int n;
        int* t;    //stores product of range
        int* d;    //lazy tree
        bool* upd;   //upd[i] = true if t[i] needs to be updated
        int uneut, qneut;

        //single element modify
        function<int(int, int)> fmodify;

        //k element modify
        function<int(int, int, int)> fmodifyk;

        //product of two elements for query
        function<int(int, int)> fcombine;

        SegtreeLazy(int maxSize, int updateNeutral, int queryNeutral, function<int(int, int)> fmodify, function<int(int, int, int)> fmodifyk, function<int(int, int)> fcombine) {
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

            t = new int[n * 2];
            d = new int[n * 2];
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

        void modify(int l, int r, int val) {    //modifies the range [l, r)
            _modify(l, r, val, 0, n, 1);
        }

        void modify(int ind, int val) {
            modify(ind, ind + 1, val);
        }

        int query(int l, int r) {   //queries the range [l, r)
            return _query(l, r, 0, n, 1);
        }

        int query(int ind) {
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

        //registers a lazy change into this node
        void apply(int ind, int val) {
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

        void _modify(int l, int r, int val, int tl, int tr, int ind) {
            if(l == r){
                return;
            }
            if(upd[ind]){
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

        int _query(int l, int r, int tl, int tr, int ind) {
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
            int lans = qneut;
            int rans = qneut;
            if(l < mid) {
                lans = _query(l, min(r, mid), tl, mid, ind * 2);
            }
            if(r > mid) {
                rans = _query(max(l, mid), r, mid, tr, ind * 2 + 1);
            }
            return fcombine(lans, rans);
        }
};

void solve(int n, int m, int w) {
    vector<vector<pair<int, int>>> walls(n, vector<pair<int, int>>(0));
    bool cover_exit = false;
    ll nr_walls = 0;
    for (int i = 0; i < w; ++i) {
        int x1, y1; cin >> x1 >> y1;
        int x2, y2; cin >> x2 >> y2;
        walls[y1].push_back({x1, x2});
        if(x2 == m - 1 && y2 == n - 1) {
            cover_exit = true;
        }
        nr_walls += x2 - x1 + 1;
    }
    if(cover_exit) {
        ll ans = (ll) n * (ll) m;
        ans -= nr_walls;
        cout << ans << "\n";
        return;
    }
    for (auto& v : walls) {
        sort(v.begin(), v.end());
    }
    ll stuck = 0;
    function<int(int, int)> fmodify = [](const int src, const int val) -> int{return val;};
    function<int(int, int, int)> fmodifyk = [](const int src, const int val, const int k) -> int{return val * k;};
    function<int(int, int)> fcombine = [](const int a, const int b) -> int{return a + b;};
    SegtreeLazy segt(m, 0, 0, fmodify, fmodifyk, fcombine);
    //cout << "MADE SEGT" << endl;
    vector<vector<pi>> ranges_unstuck(n);
    if(walls[n - 1].size()) {
        ll f_wall = walls[n - 1].back().second;
        ll wall_sum = 0;
        for(int i = 0; i < walls[n - 1].size(); i++){
            wall_sum += walls[n - 1][i].second - walls[n - 1][i].first + 1;
        }
        ranges_unstuck[n-1].push_back({f_wall+1, m});
        // segt.modify(0, f_wall + 1, 1);
        stuck += f_wall + 1 - wall_sum;
    } else {
        ranges_unstuck[n-1].push_back({0, m});
    }
    for(int i = 0; i < n; i++){
        walls[i].push_back({-1, -1});
        walls[i].push_back({m, m});
        sort(walls[i].begin(), walls[i].end());
    }
    cout << "FIRST WALL STUCK : " << stuck << "\n";
    //cout << "FINISH FIRST WALL" << endl;
    // for(int i = 0; i < n; i++){
    //     cout << segt.query(i) << " ";
    // }
    // cout << "\n";
    bool prev_nothing = false;
    ll prev_stuck = 0;


    for(int i = n - 2; i >= 0; i--){
        ll cur_stuck = 0;
        if(walls[i].size() == 2 && prev_nothing) {
            stuck += prev_stuck;
            continue;
        } 
        for(int j = 0; j < walls[i].size() - 1; j++){
            int l = walls[i][j].second + 1;
            int r = walls[i][j + 1].first;
            if(ranges_unstuck[i + 1].size() == 0){
                cur_stuck += r - l;
                continue;
            }
            int low = 0;
            int high = ranges_unstuck[i + 1].size() - 1;
            int ind = 0;
            while(low <= high) {
                int mid = low + (high - low) / 2;
                if(ranges_unstuck[i + 1][mid].first < r) {
                    ind = max(ind, mid);
                    low = mid + 1;
                }
                else {
                    high = mid - 1;
                }
            }
            if(ranges_unstuck[i + 1][ind].second <= l) {
                cur_stuck += r - l;
                continue;
            }
            int range_r = min(ranges_unstuck[i + 1][ind].second, r);
            cur_stuck += r - range_r;
            ranges_unstuck[i].push_back({l, range_r});
        }
        //cout << "SUM : " << segt.query(0, m) << "\n";
        // for(int j = 0; j < m; j++){
        //     cout << segt.query(j) << " ";
        // }
        // cout << "\n";
        if(walls[i].size() == 2){
            prev_nothing = true;
        }
        else {
            prev_nothing = false;
        }
        stuck += cur_stuck;
        prev_stuck = cur_stuck;
    }
    cout << stuck << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, w;
    cin >> n >> m >> w;
    int caseno = 0;
    while(n != 0){
        caseno ++;
        cout << "Case " << caseno << ": ";
        solve(n, m, w);
        cin >> n >> m >> w;
    }

    return 0;
}
