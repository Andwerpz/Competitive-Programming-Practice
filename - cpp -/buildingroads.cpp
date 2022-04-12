
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//CSES 1666

//generate a list of all connected components. You can treat each connected component as a node. 
//the amount of edges required to connect n nodes = n - 1. 

//to connect one component to another, you just need to connect one member of each component together

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<vector<int>> c(n, vector<int>());
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        c[a].push_back(b);
        c[b].push_back(a);
    }
    vector<bool> v(n, false);
    vector<vector<int>> groups;
    for(int i = 0; i < n; i++){
        if(v[i]){
            continue;
        }
        stack<int> s;
        vector<int> curGroup;
        v[i] = true;
        s.push(i);
        while(s.size() != 0){
            int cur = s.top();
            curGroup.push_back(cur);
            s.pop();
            for(int j : c[cur]){
                if(v[j]){
                    continue;
                }
                v[j] = true;
                s.push(j);
            }
        }
        groups.push_back(curGroup);
    }
    cout << (groups.size() - 1) << endl;
    for(int i = 0; i < groups.size() - 1; i++){
        cout << (groups[i][0] + 1) << " " << (groups[i + 1][0] + 1) << endl;
    }
    
    return 0;
}
