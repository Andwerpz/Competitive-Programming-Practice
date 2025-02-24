#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pii;
typedef pair<ll, ll> pll;
typedef vector<ll> vi;
typedef vector<ll> vl; 
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<ll>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
// typedef __ll128 lll;
// typedef __float128 lld;

//2014 NAIPC - D

//we can keep track of for each segment, how many prime factor pairs 'invalidate' it using a lazy segment tree
//let's index the segments by their left bound. Then if we have two numbers that share a prime factor at positions
//l, r, then they invalidate segments in range [r - k, l]. Note that r - k can be greater than l, so in that case 
//no segments are invalidated. 

//For each prime factor, we can keep track of all its occurrences, and then when modifying the array, just 
//add and remove segments in the segment tree. Since each number can have at most around 15 unique prime factors,
//this should run in time. 

template <typename T>
struct SegtreeLazy {
    public:
        ll n;
        T* t;    //stores product of range
        T* d;    //lazy tree
        bool* upd;  //marks whether or not a lazy change is here
        T uneut, qneut;
        function<T(T, T)> fmodify, fcombine;
        function<T(T, T, ll)> fmodifyk;

        SegtreeLazy(ll maxSize, T updateNeutral, T queryNeutral, T initVal, function<T(T, T)> fmodify, function<T(T, T, ll)> fmodifyk, function<T(T, T)> fcombine) {
            uneut = updateNeutral, qneut = queryNeutral;
            this->fmodify = fmodify;
            this->fmodifyk = fmodifyk;
            this->fcombine = fcombine;
            n = 1; //raise n to nearest pow 2
            while(n < maxSize) n <<= 1;
            t = new T[n * 2], d = new T[n * 2];
            upd = new bool[n * 2];
            for(ll i = 0; i < n; i++) t[i + n] = initVal;
            build();
        }
	
        //modifies the range [l, r)
        void modify(ll l, ll r, T val) {_modify(l, r, val, 0, n, 1);}
        void modify(ll ind, T val) {modify(ind, ind + 1, val);}
        
        //queries the range [l, r)
        T query(ll l, ll r) {return _query(l, r, 0, n, 1);}
        T query(ll ind) {return query(ind, ind + 1);}

        void assign(vector<T>& arr) {
            for(ll i = 0; i < min(n, (ll) arr.size()); i++) t[i + n] = arr[i];
            build();
        }
        void build() {
            for(ll i = n - 1; i > 0; i--) t[i] = fcombine(t[i * 2], t[i * 2 + 1]);
            for(ll i = 0; i < n * 2; i++){d[i] = uneut; upd[i] = false;}
        }

    private:
        void combine(ll ind, ll k) {
            if(ind >= n) return;
            ll l = ind * 2, r = ind * 2 + 1;
            push(l, k / 2), push(r, k / 2);
            t[ind] = fcombine(t[l], t[r]);
        }
        void apply(ll ind, T val) {
            upd[ind] = true;
            d[ind] = fmodify(d[ind], val);
        }
        void push(ll ind, ll k) {
            if(!upd[ind]) return;
            t[ind] = fmodifyk(t[ind], d[ind], k);
            if(ind < n) {
                ll l = ind * 2, r = ind * 2 + 1;
                apply(l, d[ind]), apply(r, d[ind]);
            }
            upd[ind] = false;
            d[ind] = uneut;
        }
        void _modify(ll l, ll r, T val, ll tl, ll tr, ll ind) {
            if(l == r) return;
            if(upd[ind]) push(ind, tr - tl);
            if(l == tl && r == tr) {apply(ind, val), push(ind, tr - tl); return;}
            ll mid = tl + (tr - tl) / 2;
            if(l < mid) _modify(l, min(r, mid), val, tl, mid, ind * 2);
            if(r > mid) _modify(max(l, mid), r, val, mid, tr, ind * 2 + 1);
            combine(ind, tr - tl);
        }
        T _query(ll l, ll r, ll tl, ll tr, ll ind) {
            if(l == r) return qneut;
            if(upd[ind]) push(ind, tr - tl);
            if(l == tl && r == tr) return t[ind];
            ll mid = tl + (tr - tl) / 2;
            T lans = qneut, rans = qneut;
            if(l < mid) lans = _query(l, min(r, mid), tl, mid, ind * 2);
            if(r > mid) rans = _query(max(l, mid), r, mid, tr, ind * 2 + 1);
            return fcombine(lans, rans);
        }
};

vector<ll> lp; //lowest prime factor 
vector<ll> pr; //prime list

void prime_sieve(ll n) {
    lp = vector<ll>(n + 1);
    pr = vector<ll>(0);
    for(ll i = 2; i <= n; i++) {
        if(lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
        }
        for (ll j = 0; i * pr[j] <= n; j++) {
            lp[i * pr[j]] = pr[j];
            if (pr[j] == lp[i]) {
                break;
            }
        }
    }
}

// - slow version, use when big number 
// vector<ll> find_prime_factors(ll val) {
//     vector<ll> factors(0);
//     for(int i = 0; i < pr.size(); i++){
//         while(val % pr[i] == 0){
//             factors.push_back(pr[i]);
//             val /= pr[i];
//         }
//     }
//     if(val != 1){
//         factors.push_back(val);
//     }
//     return factors;
// }

vector<ll> find_prime_factors(ll val) {
    vector<ll> factors(0);
    while(val != 1) {
        factors.push_back(lp[val]);
        ll pr = lp[val];
        while(val % pr == 0) val /= pr;
    }
    return factors;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll n, k, m; cin >> n >> k >> m;

    vector<ll> a(n);
    for (auto& x : a) {
        cin >> x;
    }

    prime_sieve(1e6);
    vvl facts(1e5 + 10);
    for(int i = 2; i < facts.size(); i++){
        facts[i] = find_prime_factors(i);
    }

    // cout << "DONE CALC PRIME" << endl;

    vector<set<ll>> psets(112345, {(ll)-1e6, (ll)1e9});

    // for (ll i = 0; i < n; ++i) {
    //     for (auto p : facts[i]) {
    //         psets[p].insert(i);
    //     }
    // }

    // {min, min cnt}
    function<pll(pll, pll)> fmodify = [](const pll src, const pll val) -> pll{
        return {src.first + val.first, src.second};
    };
    function<pll(pll, pll, ll)> fmodifyk = [](const pll src, const pll val, const ll k) -> pll{
        return {src.first + val.first, src.second};
    };
    function<pll(pll, pll)> fcombine = [](const pll a, const pll b) -> pll{
        return a.first == b.first? (pll){a.first, a.second + b.second} : (a.first < b.first? a : b);
    };
    SegtreeLazy<pll> segt(n, {0, 0}, {1e18, 0}, {0, 1}, fmodify, fmodifyk, fcombine);

    //l, r, are inclusive
    function<void(ll, ll, ll)> do_stuff = [&](ll l, ll r, ll inc) -> void {
        // cout << "L R : " << l << " " << r << "\n";
        ll lt = r - k + 1;
        ll rt = l + 1;
        rt = max(rt, lt);
        lt = max(lt, 0ll), rt = max(rt, 0ll);
        lt = min(lt, n), rt = min(rt, n);
        // cout << "LT RT : " << lt << " " << rt << " " << inc << "\n";
        segt.modify(lt, rt, {inc, 0});
    };

    for (ll i = 0; i < n; ++i) {
        // cout << "I : " << i << " " << a[i] << "\n";
        for (auto p : facts[a[i]]) {
            // cout << "P : " << p << "\n";
            ll l = -1e6, r = 1e9;
            auto it = psets[p].upper_bound(i);
            r = min(r, *it);
            // it--;
            it--;
            l = max(l, *it);
            do_stuff(l, r, -1);
            do_stuff(l, i, 1);
            do_stuff(i, r, 1);
            psets[p].insert(i);
        }
    }


    {   
        // cout << "SEGT : " << "\n";
        // for(int i = 0; i < n - k + 1; i++){
        //     cout << segt.query(i).first << " " << segt.query(i).second << "\n";
        // }
        pll q = segt.query(0, n - k + 1);
        cout << (n - k + 1) - (q.first == 0? q.second : 0) << "\n";
    }
    while (m--) {
        ll ind, val;
        cin >> ind >> val;
        ind --;
        // cout << "MODIFY : " << ind << " " << val << "\n";
        for(auto p : facts[a[ind]]) {
            psets[p].erase(ind);
            auto it = psets[p].upper_bound(ind);
            ll r = *it;
            it --;
            ll l = *it;
            do_stuff(l, ind, -1);
            do_stuff(ind, r, -1);
            do_stuff(l, r, 1);
        }
        a[ind] = val;
        for (auto p : facts[a[ind]]) {
            // cout << "P : " << p << "\n";
            ll l = -1e6, r = 1e9;
            auto it = psets[p].upper_bound(ind);
            r = min(r, *it);
            // it--;
            it--;
            l = max(l, *it);
            do_stuff(l, r, -1);
            do_stuff(l, ind, 1);
            do_stuff(ind, r, 1);
            psets[p].insert(ind);
        }
        // cout << "SEGT : " << "\n";
        // for(int i = 0; i < n - k + 1; i++){
        //     cout << segt.query(i).first << " " << segt.query(i).second << "\n";
        // }
        pll q = segt.query(0, n - k + 1);
        cout << (n - k + 1) - (q.first == 0? q.second : 0) << "\n";
    }
    ll sum = 0;
    for(ll i = 0; i < n; i++) sum += a[i];
    cout << sum << "\n";
    
    return 0;
}