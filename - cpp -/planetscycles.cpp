#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//CSES - 1751

//since each node has exactly one outgoing edge, the graph has to consist of cycles with
//spokes. 

//if a node is in a cycle, the number of nodes it will visit is the length of the cycle. 

//otherwise, the node is in a spoke, and it's just 1 plus however many nodes the node it's pointing to 
//will visit. 

vector<int> solve(vector<int>& edges) {
    int n = edges.size();
    vector<int> ans(n, -1);
    vector<bool> v(n, false);
    for(int i = 0; i < n; i++){
        if(v[i]) {
            continue;
        }
        stack<int> path;
        set<int> s;
        path.push(i);
        s.insert(i);
        v[i] = true;
        bool foundCycle = false;
        while(true) {
            int cur = path.top();
            //cout << "CUR : " << cur << "\n";
            int next = edges[cur];
            path.push(next);
            if(s.find(next) != s.end()) {
                foundCycle = true;
                break;
            }
            s.insert(next);
            if(v[next]) {
                break;
            }
            v[next] = true;
        }
        if(foundCycle) {
            //cout << "FOUND CYCLE" << "\n";
            vector<int> cycle(0);
            int cbegin = path.top();
            path.pop();
            while(true) {
                int cur = path.top();
                path.pop();
                cycle.push_back(cur);
                if(cur == cbegin) {
                    break;
                }
            }
            for(int i = 0; i < cycle.size(); i++){
                ans[cycle[i]] = cycle.size();
            }
        }
        while(path.size()) {
            int cur = path.top();
            path.pop();
            if(ans[cur] != -1){
                continue;
            }
            ans[cur] = ans[edges[cur]] + 1;
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> edges(n);
    for(int i = 0; i < n; i++){
        cin >> edges[i];
        edges[i] --;
    }
    vector<int> ans = solve(edges);
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i] << " \n"[i == ans.size() - 1];
    }
    
    return 0;
}
