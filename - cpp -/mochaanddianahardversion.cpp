#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1559D2

//got this solution from the comments section again D:
//this solution is way cleaner than the editorial solution. 

//we initially try to add all edges of the form (1, x) with 1 <= x <= n. 
//after this process, every node is connected to node 1 in at least one of the trees. 

//then, we maintain two stacks, s1, s2. s1 stores all the nodes which are connected to node 1 in the first tree
//and likewise for s2 but for the second tree. 

//then, we look at the top of the stacks, and pop until the node on top is only connected to node 1 in their respective
//tree. Since these nodes are guaranteed to be disconnected, we can go ahead and connect them. 

//keep doing this until we run out of nodes in s1 or s2. 

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
    
    int n, m1, m2;
    cin >> n >> m1 >> m2;
    DSU d1(n), d2(n);
    for(int i = 0; i < m1; i++){
        int a, b;
        cin >> a >> b;
        a --;
        b --;
        d1.unify(a, b);
    }
    for(int i = 0; i < m2; i++){
        int a, b;
        cin >> a >> b;
        a --;
        b --;
        d2.unify(a, b);
    }
    vector<pair<int, int>> ans(0);
    //connect everything to node 0
    for(int i = 1; i < n; i++){
        if(d1.find(0) != d1.find(i) && d2.find(0) != d2.find(i)) {
            ans.push_back({0, i});
            d1.unify(0, i);
            d2.unify(0, i);
        }
    }
    //ok, so for every node, it's connected to 0 in at least one of the trees. 
    stack<int> s1, s2;
    for(int i = 1; i < n; i++){
        if(d1.find(0) == d1.find(i)) {
            s1.push(i);
        }
        if(d2.find(0) == d2.find(i)) {
            s2.push(i);
        }
    }
    while(s1.size() != 0 && s2.size() != 0){
        while(s1.size() != 0 && d1.find(s1.top()) == d1.find(0) && d2.find(s1.top()) == d2.find(0)) {
            s1.pop();
        }
        while(s2.size() != 0 && d1.find(s2.top()) == d1.find(0) && d2.find(s2.top()) == d2.find(0)) {
            s2.pop();
        }
        if(s1.size() != 0 && s2.size() != 0){
            int a = s1.top();
            s1.pop();
            int b = s2.top();
            s2.pop();
            d1.unify(a, b);
            d2.unify(a, b);
            ans.push_back({a, b});
        }
    }
    cout << ans.size() << "\n";
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i].first + 1 << " " << ans[i].second + 1 << "\n";
    }
    
    return 0;
}
