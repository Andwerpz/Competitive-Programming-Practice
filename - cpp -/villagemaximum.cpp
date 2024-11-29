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

//Codeforces - 1387B2

//guessed that we should first root the tree on the centroid, and then pair nodes in
//every subtree from the root with nodes in different subtrees. 

//this makes it so that the total distance sum is equal to twice the sum of distances from
//each node to the root. 

//it's always possible to do the pairing, since the node that the tree is rooted on
//is the centroid. This means that there is no subtree with more than n / 2 nodes. 

const int N = 100005;
int sz[N];
vector<int> c[N];

int calc_sz(int cur, int p) {
    sz[cur] = 1;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p) continue;
        sz[cur] += calc_sz(next, cur);
    }
    return sz[cur];
}

int find_centroid(int cur, int p, int desire) {
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p) continue;
        if(sz[next] > desire) return find_centroid(next, cur, desire);
    }
    return cur;
}

ll mx_dist = -1;
ll calc_dist(int cur, int p, ll dist) {
    mx_dist = max(mx_dist, dist);
    ll ans = dist;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p) continue;
        ans += calc_dist(next, cur, dist + 1);
    }
    return ans;
}

void get_subt_list(int cur, int p, vi* a) {
    a->push_back(cur);
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p) continue;
        get_subt_list(next, cur, a);
    }
}

constexpr auto cmp = [](vi* a, vi* b) {
    if(a->size() == b->size()) {
        return (*a)[0] > (*b)[0];
    }
    return a->size() > b->size();
};
set<vi*, decltype(cmp)> s(cmp);
int get_next() {
    vi* a = *s.begin();
    s.erase(a);
    int ans = (*a)[a->size() - 1];
    a->pop_back();
    if(a->size() != 0) s.insert(a);
    return ans;
}

pii get_next_pair() {
    vi* a = *s.begin();
    s.erase(a);
    vi* b = *s.begin();
    s.erase(b);
    int ia = a->back();
    a->pop_back();
    int ib = b->back();
    b->pop_back();
    if(a->size() != 0) s.insert(a);
    if(b->size() != 0) s.insert(b);
    return {ia, ib};
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    for(int i = 0; i < n - 1; i++){
        int a, b;
        cin >> a >> b;
        a --;
        b --;
        c[a].push_back(b);
        c[b].push_back(a);
    }
    calc_sz(0, -1);
    int cen = find_centroid(0, -1, n / 2);
    ll ans = calc_dist(cen, -1, 0) * 2;
    // cout << "CENTROID : " << cen << "\n";
    cout << ans << "\n";
    //aggregate stuff in subtrees
    vi ansv(n, -1);
    for(int i = 0; i < c[cen].size(); i++){
        vi* a = new vi();
        get_subt_list(c[cen][i], cen, a);
        s.insert(a);
    }
    //assign centroid
    if(n % 2 == 0){
        //one other element
        int a = get_next();
        ansv[cen] = a;
        ansv[a] = cen;
    }
    else {
        //have to pick 2 elements
        pii p = get_next_pair();
        ansv[cen] = p.first;
        ansv[p.first] = p.second;
        ansv[p.second] = cen;
        // cout << "ASSIGN CEN : " << cen << " " << ia << " " << ib << endl;
    }
    //assign rest
    while(s.size() != 0){
        pii p = get_next_pair();
        ansv[p.first] = p.second;
        ansv[p.second] = p.first;
    }
    for(int i = 0; i < n; i++){
        cout << ansv[i] + 1 << " \n"[i == n - 1];
    }
    
    return 0;
}