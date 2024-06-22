#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1976E

//let's try to simulate the splitting backwards (so we're merging now). What we notice is that any value mentioned in the
//q operations now has a fixed relative position to any other value mentioned in the operations. This also means
//that if we do exactly n - 1 operations, then the entire permutation becomes fixed, which makes sense. 

//Now, we just need to place the n - q - 1 values that aren't mentioned by any operation. What we notice is that in order
//to not interfere with any of the operations, an unmentioned value x must be placed adjacent to some mentioned value y
//such that x < y. By adjacent, I mean the closest mentioned value to the left or right; unmentioned values in between
//don't matter. 

//so, what we can do is iterate through the values by descending value, keeping track of how many spots we can put the next
//unmentioned value. If the next value is mentioned, then the count increases by the number of adjacent slots that are newly
//opened up. If the next value is mentioned, then the answer is multipled by the count, and the number of slots increase 
//by 1. 

//to construct the fixed ordering of the mentioned values, we can just use dsu. 

struct DSU {
    int N;
    vector<int> dsu;
    vector<deque<int>> list;

    DSU(int n) {
        this->N = n;
        this->dsu = vector<int>(n, 0);
        for(int i = 0; i < n; i++){ //initialize roots
            dsu[i] = i;
        }
        list = vector<deque<int>>(n, deque<int>());
        for(int i = 0; i < n; i++){
            list[i].push_back(i);
        }
    }

    int find(int a) {
        if(dsu[a] == a) {
            return a;
        }
        return dsu[a] = find(dsu[a]);
    }

    //merge a on the left, b on the right
    bool unify(int a, int b) {
        int ra = find(a);
        int rb = find(b);
        if(ra == rb) {
            return false;
        }
        if(list[ra].size() < list[rb].size()) {
            while(list[ra].size() != 0){
                list[rb].push_front(list[ra].back());
                list[ra].pop_back();
            }
            dsu[ra] = rb;
        }
        else {
            while(list[rb].size() != 0){
                list[ra].push_back(list[rb].front());
                list[rb].pop_front();
            }
            dsu[rb] = ra;
        }
        return true;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    vector<int> l(q), r(q);
    for(int i = 0; i < q; i++){
        cin >> l[i];
    }
    for(int i = 0; i < q; i++){
        cin >> r[i];
    }
    DSU dsu(n);
    for(int i = q - 1; i >= 0; i--){
        dsu.unify(l[i] - 1, r[i] - 1);
    }
    vector<int> inds(n, -1);
    vector<bool> v;
    {
        deque<int> tmp = dsu.list[dsu.find(l[0] - 1)];
        v = vector<bool>(tmp.size() + 1, false);
        int ind = 0;
        while(tmp.size() != 0){
            inds[tmp.front()] = ind ++;
            tmp.pop_front();
        }
    }
    ll mod = 998244353;
    ll ans = 1;
    ll cnt = 0;
    for(int i = n - 1; i >= 0; i--){
        int ind = inds[i];
        if(ind == -1){
            ans *= cnt;
            ans %= mod;
            cnt ++;
            continue;
        }
        cnt += !v[ind];
        cnt += !v[ind + 1];
        v[ind] = true;
        v[ind + 1] = true;
    }
    cout << ans << "\n";
    
    return 0;
}