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

//Codeforces - 2001D

//maximizing the length is trivial: the length is equal to the number of unique elements in a. 
//what is harder is minimizing the lexicographical value of the resulting sequence. 

//observe that for the first element we pick, every other element must appear at least once after it. 
//We can actually apply this recursively to every element in the sequence, in other words, for every element
//in the sequence, every element after it in the sequence must appear after it in the array. 
//(putting it like this, it becomes quite trivial lol). 

//Since we want to alternate picking the maximum and minimum elements for our sequence, how can we maintain
//a set of elements that are currently valid to become the next element in the sequence?
//We can do this with the help of a range modification structure, and some amortized stuff. Keep a
//segt such that segt[i] = num unique not taken elements in pfx[i]. Initially, compute for each value, 
//the number of occurrences of that value where it's valid to become the next element in the sequence. 

//After we pick the minimum or maximum value, we can remove all occurrences of it from the valid set, 
//and increment segt[0 : l_occ] by -1, where l_occ denotes the last occurrence of the value we removed. 
//observe that although we did decrement a range by 1, any index that is valid originally, will still be 
//valid after, as the required number of unique values in the suffix changes by -1 as well. Actually, 
//the only change is that new elements will become valid, and as segt is strictly decreasing, they will
//only form directly after l_occ, so we can just do a linear scan. 

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
        int n;
        cin >> n;
        vi a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
            a[i] --;
        }
        function<int(int, int)> fmodify = [](const int src, const int val) -> int{return src + val;};
        function<int(int, int, int)> fmodifyk = [](const int src, const int val, const int k) -> int{return src + val;};
        function<int(int, int)> fcombine = [](const int a, const int b) -> int{return min(a, b);};
        SegtreeLazy<int> segt(n + 1, 0, 1e9, 0, fmodify, fmodifyk, fcombine);
        //compute number of unique values in each suffix
        {
            set<int> s;
            for(int i = n - 1; i >= 0; i--){
                s.insert(a[i]);
                segt.modify(i, s.size());
            }
        }
        int req = segt.query(0) - 1;
        vi ans(0);
        set<int> taken;
        map<int, int> val;
        vi n_occ(n, n);
        map<int, set<int>> occ;
        {
            vi p(n, n);
            for(int i = n - 1; i >= 0; i--){
                n_occ[i] = p[a[i]];
                p[a[i]] = i;
                if(segt.query(i) > req) {
                    val[a[i]] ++;
                }
                occ[a[i]].insert(i);
            }
        }
        int ptr = 0;
        bool choose_max = true;
        while(req != -1) {
            // cout << "VAL : " << val.size() << endl;
            int cur = (choose_max? val.rbegin()->first : val.begin()->first);
            ans.push_back(cur);
            taken.insert(cur);
            val.erase(cur);
            int l_occ = *occ[cur].rbegin();
            segt.modify(0, l_occ, -1);
            int nptr = *occ[cur].begin() + 1;
            // cout << "CUR : " << cur << " " << nptr << endl;
            if(nptr < ptr){
                break;
            }
            req --;
            choose_max = !choose_max;
            while(ptr != nptr) {
                int next = a[ptr];
                ptr ++;
                if(taken.count(next)) {
                    continue;
                }
                val[next] --;
                if(val[next] == 0){
                    val.erase(next);
                }
                // cout << "ERASE OCC : " << next << " " << ptr << endl;
                occ[next].erase(ptr - 1);
                // cout << "BEGIN : " << *occ[next].begin() << endl;
            }
            for(int j = l_occ + 1; j < n; j++){
                if(segt.query(j) <= req) {
                    break;
                }
                if(taken.count(a[j])) {
                    continue;
                }
                val[a[j]] ++;
            }
        }
        cout << ans.size() << "\n";
        for(int i = 0; i < ans.size(); i++){
            cout << ans[i] + 1 << " ";
        }
        cout << "\n";
    }
    
    return 0;
}