#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//A&M Fall Contest I

//consider the case where you can only build one generator. If that is the case, then the solution to the problem
//is to find the minimum spanning tree connecting all the nodes, as it doesn't matter where you build the generator
//since all nodes have to be connected anyways. 

//next, consider that you have a 'dummy node', g, where you can place your one generator. Any power line built from
//g to another node, a, costs c, which is the cost to build a generator. Notice that building a generator at
//a is identical to building a connection from g to a. So finding the minimum spanning tree with g included is identical to
//solving the original problem. 

int find(vector<int>& c, int a) {
    if(c[a] == a){
        return a;
    }
    return c[a] = find(c, c[a]);
}

bool unify(vector<int>& c, int a, int b){
    int aRoot = find(c, a);
    int bRoot = find(c, b);
    c[aRoot] = bRoot;
    return aRoot != bRoot;  //if they are equal, then nothing changes
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, c;
    cin >> n >> m >> c;
    vector<int> dsu(n + 1);
    for(int i = 0; i < dsu.size(); i++){
        dsu[i] = i;
    }    
    vector<vector<int>> conn(0);
    for(int i = 0; i < m; i++){
        int a, b, cost;
        cin >> a >> b >> cost;
        a --;
        b --;
        conn.push_back({a, b, cost});
    }
    for(int i = 0; i < n; i++){
        conn.push_back({i, n, c});
    }
    sort(conn.begin(), conn.end(), [](vector<int>& a, vector<int>& b) -> bool {return a[2] < b[2];});
    int costTot = 0;
    vector<int> g(0);
    vector<pair<int, int>> builtP(0);
    for(vector<int> i : conn){
        int a = i[0];
        int b = i[1];
        int cost = i[2];
        if(unify(dsu, a, b)) {
            if(a == n || b == n){
                g.push_back(min(a, b));
            }
            else {
                builtP.push_back({a, b});
            }
            costTot += cost;
        }
    }
    cout << costTot << " " << g.size() << " " << builtP.size() << "\n";
    for(int i : g){
        cout << (i + 1) << "\n";
    }
    for(pair<int, int> i : builtP){
        cout << (i.first + 1) << " " << (i.second + 1) << "\n";
    }
    
    return 0;
}
