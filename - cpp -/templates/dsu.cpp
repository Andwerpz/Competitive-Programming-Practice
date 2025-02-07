#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//basic union find implementation with path compression and small to large merging

struct DSU {
    int N;
    vector<int> dsu, sz;

    DSU() {}
    DSU(int n) {
        this->N = n;
        this->dsu = vector<int>(n, 0);
        this->sz = vector<int>(n, 1);
        for(int i = 0; i < n; i++){ //initialize roots
            dsu[i] = i;
        }
    }

    int find(int a) {
        if(dsu[a] == a) {
            return a;
        }
        return dsu[a] = find(dsu[a]);
    }

    int get_sz(int a){
        return sz[find(a)];
    }

    //ret true if updated something
    bool unify(int a, int b) {
        int ra = find(a);
        int rb = find(b);
        if(ra == rb) {
            return false;
        }
        if(sz[rb] > sz[ra]) swap(ra, rb);
        //merge rb into ra
        dsu[rb] = ra;
        sz[ra] += sz[rb];
        return true;
    }
};

//dsu with rollback. 
//idea is to observe that every time you unify, just one node changes, so keep track of those changes within
//a stack and revert them one by one. 
//can't use path compression as its gains are amortized and don't work well with rollback. 
//call rollback() to revert the most recent unify, whether successful or not. 
struct DSU_RLB {
    int N;
    vector<int> dsu, sz;
    stack<array<int, 3>> rlb;  //{ra, rb, sz}

    DSU_RLB() {}
    DSU_RLB(int n) {
        this->N = n;
        this->dsu = vector<int>(n, 0);
        this->sz = vector<int>(n, 1);
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
            rlb.push({-1, 0, 0});
            return false;
        }
        if(sz[rb] > sz[ra]) swap(ra, rb);
        //merge rb into ra
        rlb.push({ra, rb, sz[ra]});
        dsu[rb] = ra;
        sz[ra] += sz[rb];
        return true;
    }

    void rollback() {
        if(rlb.size() == 0) return;
        if(rlb.top()[0] == -1) {rlb.pop(); return;}
        int ra = rlb.top()[0], rb = rlb.top()[1];
        dsu[rb] = rb;
        sz[ra] = rlb.top()[2];
        rlb.pop();
    }
};
