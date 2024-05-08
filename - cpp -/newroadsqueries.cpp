#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//CSES - 2101

//this TLE, but i think it's O(n * log(n)^2). 

struct DSU {
    int N;
    vector<int> dsu;
    vector<set<int>> cmp;
    vector<set<pair<int, int>>> q;

    DSU(int n) {
        this->N = n;
        this->dsu = vector<int>(n, 0);
        this->cmp = vector<set<int>>(n);
        this->q = vector<set<pair<int, int>>>(n);
        for(int i = 0; i < n; i++){ //initialize roots
            dsu[i] = i;
            cmp[i].insert(i);
        }
    }

    void add_q(int a, int b) {
        q[a].insert({a, b});
        q[b].insert({b, a});
    }

    void dsu_init() {
        for(int i = 0; i < N; i++){
            dsu[i] = i;
        }
    }

    int find(int a) {
        if(dsu[a] == a) {
            return a;
        }
        return dsu[a] = find(dsu[a]);
    }

    //return list of queries that have been satisfied. 
    vector<pair<int, int>> unify(int a, int b) {
        vector<pair<int, int>> ansq(0);
        int ra = find(a);
        int rb = find(b);
        if(ra == rb) {
            return ansq;
        }
        //which one has less cost to merge?
        if(cmp[rb].size() + q[rb].size() < cmp[ra].size() + q[ra].size()) {
            swap(ra, rb);
        }
        //merge rb into ra
        for(auto i = q[rb].begin(); i != q[rb].end(); i++){
            int qa = i -> first;
            int qb = i -> second;
            if(cmp[ra].count(qb)) {
                ansq.push_back({qa, qb});
            }
            else {
                q[ra].insert({qa, qb});
            }
        }
        for(auto i = cmp[rb].begin(); i != cmp[rb].end(); i++){
            cmp[ra].insert(*i);
        }
        dsu[rb] = ra;
        return ansq;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m, qcnt;
    cin >> n >> m >> qcnt;
    DSU dsu(n);
    vector<pair<int, int>> c(m);
    for(int i = 0; i < m; i++){
        cin >> c[i].first >> c[i].second;
        c[i].first --;
        c[i].second --;
    }
    vector<pair<int, int>> q(qcnt);
    for(int i = 0; i < qcnt; i++){
        cin >> q[i].first >> q[i].second;
        q[i].first --;
        q[i].second --;
        dsu.add_q(q[i].first, q[i].second);
    }
    map<pair<int, int>, int> qans;
    for(int i = 0; i < m; i++){
        vector<pair<int, int>> ansq = dsu.unify(c[i].first, c[i].second);
        for(int j = 0; j < ansq.size(); j++){
            pair<int, int> p = ansq[j];
            qans.insert({p, i + 1});
            swap(p.first, p.second);
            qans.insert({p, i + 1});
        }
    }
    for(int i = 0; i < q.size(); i++){
        if(!qans.count(q[i])) {
            cout << "-1\n";
        }
        else {
            cout << qans[q[i]] << "\n";
        }
    }
    
    return 0;
}
