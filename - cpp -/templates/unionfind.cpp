#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//basic union find implementation with path compression

const int N = 1e6;
vector<int> dsu(N, 0);

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    
    
    return 0;
}
