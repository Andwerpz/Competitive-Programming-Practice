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

//UIUC IPL Team Tryout 2025 - D

//had some TLE issues with my small to large merging, not sure what's going on with that.

//we'll solve each subtree from the root up. From each subtree we'll return the subtree's known sum, and
//the list of still unknown leaves in the subtree. 

//if the subtree has a known root, then we need to be able to resolve all the unknowns in the subtree. 
//either there are no unknowns, or there is one unknown and we can assign to that unknown the difference
//between the root value and the actual sum, or the difference is exactly equal to the number of unknowns
//in which case we can give each unknown a value of 1

//if the subtree has an unknown root, then we just propgate everything upwards. 

vvi c;
vl a;

void is_impossible() {
    cout << "impossible\n";
    exit(0);
}

//returns known sum
pair<ll, vi*> solve(ll cur) {
    // cout << "SOLVE : " << cur << endl;
    if(c[cur].size() == 0) {
        // cout << "LEAF : " << endl;
        // cout << "DONE ALLOC : " << ret << endl;
        if(a[cur] == 0) return {0, new vi(1, cur)};
        return {a[cur], new vi()};
    }

    vi* unk = new vi();
    ll ksum = 0;
    for(ll x : c[cur]) {
        // cout << "ITER : " << x << endl;
        pair<ll, vi*> ret = solve(x);
        // cout << "RET : " << x << endl;
        ksum += ret.first;
        // cout << "RET.SECOND : " << ret.second << endl;
        if(unk->size() < ret.second->size()) swap(unk, ret.second);
        for(int i = 0; i < ret.second->size(); i++) unk->push_back(ret.second->at(i));
        // cout << "DONE  : " << x << endl;
    }
    // cout << "HERE" << endl;

    if(a[cur] == 0) {
        return {ksum, unk};
    }
    else {
        ll diff = a[cur] - ksum;
        if(diff < 0) is_impossible();
        if(diff == 0) {
            if(unk->size() != 0) is_impossible();
            return {a[cur], new vi()};
        }
        if(unk->size() == 1) {
            a[unk->at(0)] = diff;
            return {a[cur], new vi()};
        }
        if(unk->size() != diff) is_impossible();
        for(int i = 0; i < unk->size(); i++) a[unk->at(i)] = 1;
        return {a[cur], new vi()};
    }
}

ll construct(ll cur) {
    if(c[cur].size() == 0) {
        assert(a[cur] != 0);
        return a[cur];
    }
    ll sum = 0;
    for(ll x : c[cur]) sum += construct(x);
    if(a[cur] == 0) a[cur] = sum;
    assert(a[cur] == sum);
    return sum;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll n;
    cin >> n;
    c = vvi(n);
    a = vl(n);
    for(ll i = 1; i < n; i++){
        ll p;
        cin >> p;
        p --;
        c[p].push_back(i);
    }
    for(ll i = 0; i < n; i++) cin >> a[i];
    pair<ll, vi*> ret = solve(0);
    if(ret.second->size() != 0) is_impossible();
    construct(0);
    for(ll i = 0; i < n; i++) cout << a[i] << "\n";
    
    return 0;
}