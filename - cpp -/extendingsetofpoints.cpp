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

//Codeforces - 1140F

//clever use of range updates and dsu with rollback. 

//first, given some S, how can we determine the size of E(S)? Consider a geometric interpretation of the problem:
//we have a bunch of points on the 2D plane, and if there exists a point such that filling it in will complete some
//rectangle, then we can add it to E(S). 

//Consider connecting any two points that are horizontally or vertically adjacent. Then, each component can 
//be expanded out to a complete rectangle, so each component is going to add X * Y points to E(S), where X and Y
//are the number of unique x and y coordinates in that component respectively. 

//naturally, this leads to a DSU solution, we even get insertions for free. However, deletions from S are much trickier.

//How can we deal with deletions? Well the trick is to avoid them (kind of). With DSU, we can implement a rollback that 
//can undo the last operation in O(1). So we want to arrange the insertions and deletions in a specific way such that 
//there aren't that many of them, and they can be handled using rollback. 

//Consider when some specific point p is present in S. It's presence across queries can be represented by some set
//of disjoint segments. Now, consider some sort of segment tree, and inserting p into the nodes of the tree such that 
//its presence across queries is accurately represented. Then, if we do a dfs into the tree, adding to S when we dfs
//into a node, and removing from S when exiting from a node, once we reach the leaf we'll have all the points that
//are present at the time in S. And, since it's dfs, it can be used with rollback because its essentially a stack. 

//Observe that in the worst case, each segment will be added to at most log(n) segments, so we will have to do at most
//O(n * log(n)) insertions and deletions to the DSU. So the total complexity is O(n * log(n)^2). 

struct DSU {
    int N;
    vector<int> dsu, sz;
    vl xc, yc;
    stack<array<int, 5>> rlb;  //{ra, rb, sz, xc, yc}
    ll cans = 0;

    DSU() {}
    DSU(int n) {
        this->N = n;
        this->dsu = vector<int>(n, 0);
        this->sz = vector<int>(n, 1);
        xc = vl(n, 0);
        yc = vl(n, 0);
        for(int i = 0; i < n; i++){ //initialize roots
            dsu[i] = i;
        }
    }

    int find(int a) {
        return dsu[a] == a? a : find(dsu[a]);
    }

    int get_sz(int a){
        return sz[find(a)];
    }

    //ret true if updated something
    bool unify(int a, int b) {
        int ra = find(a);
        int rb = find(b);
        if(ra == rb) {
            //push dummy thing to roll back
            rlb.push({-1, 0, 0, 0, 0});
            return false;
        }
        if(sz[rb] > sz[ra]) swap(ra, rb);
        //merge rb into ra
        rlb.push({ra, rb, sz[ra], (int) xc[ra], (int) yc[ra]});
        cans -= xc[ra] * yc[ra] + xc[rb] * yc[rb];
        dsu[rb] = ra;
        sz[ra] += sz[rb];
        xc[ra] += xc[rb];
        yc[ra] += yc[rb];
        cans += xc[ra] * yc[ra];
        return true;
    }

    void rollback() {
        if(rlb.size() == 0) return;
        if(rlb.top()[0] == -1) {rlb.pop(); return;}
        int ra = rlb.top()[0], rb = rlb.top()[1];
        cans -= xc[ra] * yc[ra];
        dsu[rb] = rb;
        sz[ra] = rlb.top()[2];
        xc[ra] = rlb.top()[3];
        yc[ra] = rlb.top()[4];
        cans += xc[ra] * yc[ra] + xc[rb] * yc[rb];
        rlb.pop();
    }
};

const int N = 3e5 + 10;
int tn = 1;
vector<vector<pii>> segt;
vl ans;
DSU dsu;

void insert_segt(int l, int r, pii val, int tl = 0, int tr = tn, int ind = 1) {
    if(l == r) return;
    if(l == tl && r == tr) {segt[ind].push_back(val); return;}
    int mid = tl + (tr - tl) / 2;
    if(l < mid) insert_segt(l, min(r, mid), val, tl, mid, ind * 2);
    if(r > mid) insert_segt(max(l, mid), r, val, mid, tr, ind * 2 + 1);
}

void dfs(int ind = 1, int l = 0, int r = tn) {
    for(pii x : segt[ind]) dsu.unify(x.first, x.second + N);
    if(ind >= tn) {
        ans[ind - tn] = dsu.cans;
    }
    else {
        dfs(ind * 2, l, l + (r - l) / 2);
        dfs(ind * 2 + 1, l + (r - l) / 2, r);
    }
    for(pii x : segt[ind]) dsu.rollback();
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    dsu = DSU(N * 2);
    for(int i = 0; i < N; i++) dsu.xc[i] = 1, dsu.yc[i + N] = 1;
    int n;
    cin >> n;
    vector<pii> a(n);
    for(int i = 0; i < n; i++) cin >> a[i].first >> a[i].second;
    while(tn < n) tn *= 2;
    segt = vector<vector<pii>>(tn * 2);
    ans = vl(tn);
    map<pii, int> s;
    for(int i = 0; i < n; i++){
        if(s.count(a[i])) {
            insert_segt(s[a[i]], i, a[i]);
            s.erase(a[i]);
        }
        else {
            s[a[i]] = i;
        }
    }
    for(auto i = s.begin(); i != s.end(); i++){
        insert_segt(i->second, n, i->first);
    }
    dfs();
    for(int i = 0; i < n; i++) cout << ans[i] << " ";
    cout << "\n";
    
    return 0;
}