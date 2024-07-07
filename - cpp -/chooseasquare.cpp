#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1221F

//figuring out the solution is half of the problem, implementation is the other (bigger) half. 

//let's first ignore the side length cost of the square, and solve the problem as if that didn't exist. 

//from each point, draw a vertical and horizontal line and mark where it intersects with the xy line. Notice that
//in order for a square to contain a point, it needs to contain both the intersections on the xy line. So we can
//replace all the points with intervals on the xy line, and in order for the square to contain a point, it needs
//to entirely contain it's associated interval. 

//more specifically, if a point is at (x, y), then it's interval is [min(x, y), max(x, y)]. 

//if we fix the square interval to start at 0, then we can pretty easily solve the problem. If we iterate the 
//right bound of the square interval, notice that we only get a points value when we cross the point interval's
//right bound. So essentially, we're trying to find the maximum value in a prefix sum, where we increment each
//point on their right bound by their value. We can find this quickly using a segment tree over the prefix sum. 

//now, lets say the square interval starts at 1. We just have to notice that any point that has left bound
//at 0 is now impossible to contain completely, so we can go ahead and remove those points from the prefix sum. 
//Luckily, if we use lazy segment tree, we can quickly do a range query to remove those points. 

//With a lazy segment tree, handling the side length cost of the square is also pretty easy. If the square interval
//is fixed at 0, then the prefix sum should initially have [0, -1, -2, ...] on top of whatever point interval values
//there are. Then, when the square interval goes to 1, we can add 1 to every element. 

//note that you also have to do coordinate compression since the range of coordinates can be up to 1e9. 

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

typedef tuple<ll, ll> tll;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<pair<pair<int, int>, ll>> a(0);
    for(int i = 0; i < n; i++){
        int x, y, c;
        cin >> x >> y >> c;
        int l = min(x, y);
        int r = max(x, y);
        a.push_back({{l, r}, c});
    }
    //apply coordinate compression
    map<int, int> cm, rm;
    {
        set<int> s;
        s.insert((int) (1.5 * 1e9));
        for(int i = 0; i < a.size(); i++) {
            s.insert(a[i].first.first);
            s.insert(a[i].first.second);
        }
        int ptr = 0;
        for(auto i = s.begin(); i != s.end(); i++){
            cm[*i] = ptr;
            rm[ptr] = *i;
            ptr ++;
        }
    }
    int cn = cm.size();
    for(int i = 0; i < a.size(); i++){
        int l = a[i].first.first;
        int r = a[i].first.second;
        a[i].first.first = cm[a[i].first.first];
        a[i].first.second = cm[a[i].first.second];
    }
    function<tll(tll, tll)> fmodify = [](const tll src, const tll val) -> tll{
        return {get<0>(src), get<1>(src) + get<1>(val)};
    };
    function<tll(tll, tll, int)> fmodifyk = [](const tll src, const tll val, const int k) -> tll{
        return {get<0>(src), get<1>(src) + get<1>(val)};
    };
    function<tll(tll, tll)> fcombine = [](const tll a, const tll b) -> tll{
        return get<1>(a) > get<1>(b)? a : b;
    };
    SegtreeLazy<tll> segt(cn, {0, 0}, {-1, -1e18}, {-1, -1e18}, fmodify, fmodifyk, fcombine);
    {
        vector<tll> init(0);
        for(int i = 0; i < cn; i++){
            init.push_back({i, -rm[i]});
        }
        segt.assign(init);
    }
    sort(a.begin(), a.end());
    for(int i = 0; i < n; i++){
        int r = a[i].first.second;
        segt.modify(r, cn, {0, a[i].second});
    }
    ll ans = 0;
    pair<int, int> ansr = {cn - 1, cn - 1};
    int ptr = 0;
    int prev = 0;
    for(int i = 0; i < cn; i++){
        //account for square cost
        int cur = rm[i];
        segt.modify(0, cn, {0, cur - prev});
        prev = cur;
        if(ptr != n && a[ptr].first.first == i){
            tll q = segt.query(i, cn);
            if(get<1>(q) > ans) {
                ans = get<1>(q);
                ansr = {i, get<0>(q)};
            }
        }
        while(ptr != n && a[ptr].first.first == i) {
            int r = a[ptr].first.second;
            segt.modify(r, cn, {0, -a[ptr].second});
            ptr ++;
        }
    }
    cout << ans << "\n";
    int x = rm[ansr.first];
    int y = rm[ansr.second];
    cout << x << " " << x << " " << y << " " << y << "\n";
    
    return 0;
}