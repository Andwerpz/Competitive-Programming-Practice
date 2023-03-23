#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 08 B

//bipartite graph problem

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<string> names(n, "");
    map<string, int> mp;
    for(int i = 0; i < n; i++){
        cin >> names[i];
        mp.insert({names[i], i});
    }
    vector<vector<int>> c(n, vector<int>(0));
    int m;
    cin >> m;
    for(int i = 0; i < m; i++){
        string a, b;
        cin >> a >> b;
        int u = mp.find(a) -> second;
        int v = mp.find(b) -> second;
        c[u].push_back(v);
        c[v].push_back(u);
    }
    vector<bool> v(n, false);
    vector<int> type(n, -1);
    bool isValid = true;
    for(int j = 0; j < n; j++){
        if(v[j] == true){
            continue;
        }
        type[j] = 0;
        v[j] = true;
        stack<int> s;
        s.push(j);
        while(s.size() != 0){
            int cur = s.top();
            s.pop();
            for(int i = 0; i < c[cur].size(); i++){
                int next = c[cur][i];
                if(type[next] == type[cur]) {
                    isValid = false;
                }
                if(v[next]) {
                    continue;
                }
                v[next] = true;
                type[next] = type[cur] == 0? 1 : 0;
                s.push(next);
            }
        }
    }
    if(isValid){
        for(int i = 0; i < n; i++){
            if(type[i] == 0){
                cout << names[i] << " ";
            }
        }
        cout << "\n";
        for(int i = 0; i < n; i++){
            if(type[i] == 1){
                cout << names[i] << " ";
            }
        }
        cout << "\n";
    }
    else {
        cout << "impossible\n";
    }
    
    return 0;
}
