
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

vector<vector<int>> c;
vector<int> cycle = vector<int>();
vector<bool> v;
set<int> curPath;

//CSES 1669

//we pretty much have to find cycles within the graph of length 3 or greater. 

//since the cycles have to be length 3 or greater, we know we can't just jump back and forth between two nodes. 
//we have to find non-trivial cycles. 

//We can do a dfs search from a node, keeping track of the path that we took to get from the original node to the
//node that we are currently searching in. If we ever intersect with our path, then we know that we have found a cycle, 
//and we can backtrack to get the ans. 

//tip: use recursion for this one.

bool findCycle(int parent, int cur){
    v[cur] = true;
    curPath.insert(cur);
    for(int i : c[cur]){
        if(i == parent){
            continue;
        }
        if(curPath.find(i) != curPath.end()){   //found a cycle; end case
            cycle.push_back(i);
            cycle.push_back(cur);
            return true;
        }
        if(v[i]){
            continue;
        }
        if(findCycle(cur, i)){
            cycle.push_back(cur);
            return true;
        }
    }
    curPath.erase(cur);
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    c = vector<vector<int>>(n, vector<int>());
    v = vector<bool>(n);
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        c[a].push_back(b);
        c[b].push_back(a);
    }
    bool foundCycle = false;
    for(int i = 0; i < n; i++){
        if(v[i]){
            continue;
        }
        curPath = set<int>();
        curPath.insert(i);
        if(findCycle(-1, i)){
            foundCycle = true;
            break;
        }
    }
    if(!foundCycle){
        cout << "IMPOSSIBLE\n";
    }
    else {
        vector<int> ans;
        int first = cycle[0];
        ans.push_back(first);
        for(int i = 1; i < cycle.size(); i++){
            ans.push_back(cycle[i]);
            if(cycle[i] == first){
                break;
            }
        }
        cout << ans.size() << endl;
        for(int i : ans){
            cout << (i + 1) << " ";
        }
        cout << endl;
    }
    
    return 0;
}
