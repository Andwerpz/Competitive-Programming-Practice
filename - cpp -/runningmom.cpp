#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Kattis - runningmom

//we want to find all nodes that can't lead to a cycle. 
//if we reverse all the edges, and run toposort, then any nodes that we *can toposort will not lead to a cycle. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    map<string, int> m;
    vector<vector<int>> c(n, vector<int>(0));
    vector<int> indeg(n, 0);
    for(int i = 0; i < n; i++){
        string s0, s1;
        cin >> s0 >> s1;
        if(!m.count(s0)) {
            m[s0] = m.size();
        }
        if(!m.count(s1)){
            m[s1] = m.size();
        }
        c[m[s1]].push_back(m[s0]);
        indeg[m[s0]] ++;
    }
    vector<bool> rm(n, false);
    queue<int> q;
    for(int i = 0; i < n; i++){
        if(indeg[i] == 0){
            q.push(i);
        }
    }
    while(q.size() != 0){
        int cur = q.front();
        q.pop();
        rm[cur] = true;
        for(int i = 0; i < c[cur].size(); i++){
            int next = c[cur][i];
            indeg[next] --;
            if(indeg[next] == 0){
                q.push(next);
            }
        }
    }
    string line;
    getline(cin, line);
    getline(cin, line);
    while(!cin.eof()) {
        int ind = m[line];
        cout << line << " " << (rm[ind]? "trapped" : "safe") << "\n";
        getline(cin, line);
    }
    
    return 0;
}
