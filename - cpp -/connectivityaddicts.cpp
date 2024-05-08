#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1738F

//notice that if we were to determine for each node, the connected component it belonged to, we could
//just color each connected component the same color, and that coloring would satisfy the requirements. 

//the problem is, identifying the connected components given n queries is very hard (or impossible idk), so
//we have to use a different strategy. 

//let's pick the node with the highest degree. If at the beginning we query this node for all of its neighbors, 
//we can just color it and all of it's neighbors the same color, and that's a valid coloring (for it and it's neighbors).
//this is because no node has a higher degree than the one we picked, and so if the degree of that node was d, 
//then the degree sum can be at most d^2, but the number of nodes squared is (d + 1)^2. 

//then, we consider the rest of the unvisited nodes in descending order of degree. When querying for their neighbors, one
//of two cases can happen:

//1 - none of our neighbors have been visited before: in this case, we can act identically to the node with the greatest
//degree. 

//2 - one of our neighbors have been visited before: now, we can just add whatever nodes we found to the visited node's 
//component, and move on to the next node. 

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<pair<int, int>> d(n);
        for(int i = 0; i < n; i++){
            cin >> d[i].first;
            d[i].second = i;
        }
        sort(d.begin(), d.end());
        reverse(d.begin(), d.end());
        vector<bool> v(n, false);
        DSU dsu(n);
        for(int i = 0; i < n; i++){
            int cur = d[i].second;
            if(v[cur]){
                continue;
            }
            v[cur] = true;
            for(int j = 0; j < d[i].first; j++){
                cout << "? " << cur + 1 << endl;
                int next;
                cin >> next;
                next --;
                dsu.unify(cur, next);
                if(v[next]) {
                    break;
                }
                v[next] = true;
            }
        }
        cout << "! ";
        for(int i = 0; i < n; i++){
            cout << dsu.find(i) + 1 << " ";
        }
        cout << endl;
    }
    
    return 0;
}
