#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//basic union find implementation with path compression
struct DSU {
    int N;
    vector<int> dsu;

    DSU(int n) {
        this->N = n;
        this->dsu = vector<int>(n, 0);
        for(int i = 0; i < n; i++){ //initialize roots
            dsu[i] = i;
        }
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

    //ret true if updated something
    bool unify(int a, int b) {
        int ra = find(a);
        int rb = find(b);
        if(ra == rb) {
            return false;
        }
        dsu[rb] = ra;
        
        return true;
    }
};
