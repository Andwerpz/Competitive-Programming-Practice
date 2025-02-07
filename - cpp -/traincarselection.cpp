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
typedef __int128 lll;
// typedef __float128 lld;

//Codeforces - 1137E

//line container jank

//we can consider train cars added to the head and cars added to the tail seperately. 

//among all cars added to the head, the frontmost car will always be the best. We can just keep track of
//the value of the frontmost car seperately, resetting it to 0 when we add more head cars

//with the tail cars, if we consider the tail cars from last to first, notice that a[i] decreases until 
//it reaches a new added section, then it jumps up. Therefore, there are at most m local minima that
//we will need to worry about. 

//we can first reindex every car by considering their distance from the original first head car. Then, every
//convenience recalculation query we can consider as effecting the head and tail cars seperately, we just have
//to add to b, s * (amt of head cars) and then it's as if it just affects the tail cars

//this is nice because now, we can express the increase due to s as s * (dist from original head). Now, 
//for each local minimum, interpret the convenience as a linear function wrt sum of s. We just want to find
//the minimum value out of all lines given some sum of s. This can be done in O(log(n)) using a li chao tree.

//add lines of form kx + m and query maximum value at some point x
//O(log(n)) time per add / query
struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	static const ll inf = LLONG_MAX;
	ll div(ll a, ll b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll k, ll m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	pll query(ll x) {   //{max val, max k}
		assert(!empty());
		auto l = *lower_bound(x);
        ll val = l.k * x + l.m;
        ll mxk = l.k;
        {
            auto ptr = lower_bound(x);
            if(ptr != end()) {
                ptr ++;
                lll nval = ptr->k * x + ptr->m;
                if(nval == val) mxk = max(mxk, ptr->k);
            }
        }
        {
            auto ptr = lower_bound(x);
            if(ptr != begin()) {
                ptr --;
                lll nval = ptr->k * x + ptr->m;
                if(nval == val) mxk = max(mxk, ptr->k);
            }
        }
		return {val, mxk};
	}
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll n, m;
    cin >> n >> m;
    //run through all queries and figure out initial position of carts 
    ll l = 0, r = n;   //r is head, l is tail - 1
    ll ans = 1e18 + 100;
    ll cx = n;
    ll first = 0, dec = 0, ldec = 0;
    ll sc = 0, lsc = 0;  //s coord
    LineContainer lc;
    for(int i = 0; i < m; i++){
        int type;
        cin >> type;
        if(type == 1){  //add to head
            ll k;
            cin >> k;
            r += k;
            first = 0;
        }
        else if(type == 2){ //add to tail
            //change cx
            lc.add(-(n - cx), -(-ldec - (n - cx) * lsc));
            cx = l;
            ldec = dec, lsc = sc;
            ll k;
            cin >> k;
            l -= k;
        }
        else if(type == 3){ //add value
            ll b, s;
            cin >> b >> s;
            first += b;
            //adjust so that it 'starts' at n
            b += (r - n) * s;
            dec += b;
            sc += s;
        }
        ll cans = first, cid = 1;
        if(lc.size() != 0){
            pll p = lc.query(sc);
            p.first *= -1;
            p.first += dec;
            if(p.first < cans) {
                cans = p.first, cid = (-p.second) + r - n + 1;
            }
        }
        {
            ll val = (n - cx) * (sc - lsc) + (dec - ldec);
            if(val < cans) cans = val, cid = r - cx + 1;
        }
        cout << cid << " " << cans << "\n";
    }
    
    return 0;
}