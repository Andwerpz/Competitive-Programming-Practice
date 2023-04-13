#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 10 A

//notice that if we consider this as a directed graph where if person a can be understood by person b, 
//we draw an edge from a to b, then a strongly connected component in the graph means that 
//everyone can be understood by everyone else through some path in the component

//thus, we just need to find the largest connected component, and everyone not in that component has to leave. 

void visit(int i, stack<int>& s, vector<bool>& v, vector<vector<int>>& c) {
    if(v[i]) {
        return;
    }
    v[i] = true;
    for(int j = 0; j < c[i].size(); j++){
        visit(c[i][j], s, v, c);
    }
    s.push(i);
}

void assign(int i, int root, vector<int>& ans, vector<bool>& v, vector<vector<int>>& rc) {
    if(v[i]){
        return;
    }
    v[i] = true;
    ans[i] = root;
    for(int j = 0; j < rc[i].size(); j++){
        assign(rc[i][j], root, ans, v, rc);
    }
}

vector<int> findSCC(int n, vector<vector<int>>& c) {
    vector<vector<int>> rc(n, vector<int>(0));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < c[i].size(); j++){
            rc[c[i][j]].push_back(i);
        }
    }
    vector<int> ans(n, 0);
    vector<bool> v(n, false);
    stack<int> s;
    for(int i = 0; i < n; i++){
        visit(i, s, v, c);
    }
    fill(v.begin(), v.end(), false);
    while(s.size() != 0){
        int next = s.top();
        s.pop();
        assign(next, next, ans, v, rc);
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    map<string, int> nMap;
    map<string, int> lMap;
    vector<pair<int, string>> nRMap(0);
    vector<pair<int, string>> lRMap(0);
    vector<vector<int>> c(n, vector<int>(0));
    vector<vector<int>> understand(n, vector<int>(0));
    string tmp;
    getline(cin, tmp);
    for(int i = 0; i < n; i++){
        string line;
        vector<string> a;
        getline(cin, line);
        int prev = 0;
        for(int j = 0; j < line.size(); j++){
            if(line[j] == ' '){
                a.push_back(line.substr(prev, j - prev));
                prev = j + 1;
            }
        }
        a.push_back(line.substr(prev, line.size() - prev));
        string name = a[0];
        if(nMap.find(name) == nMap.end()) {
            nMap.insert({name, nRMap.size()});
            nRMap.push_back({nRMap.size(), name});
        }
        for(int j = 1; j < a.size(); j++){
            if(lMap.find(a[j]) == lMap.end()) {
                lMap.insert({a[j], lRMap.size()});
                lRMap.push_back({lRMap.size(), a[j]});
            }
            understand[i].push_back(lMap.find(a[j]) -> second);
        }
    }
    for(int i = 0; i < n; i++){
        int speak = understand[i][0];
        for(int j = 0; j < n; j++){
            if(j == i){
                continue;
            }
            bool isValid = false;
            for(int k = 0; k < understand[j].size(); k++){
                if(understand[j][k] == speak) {
                    isValid = true;
                    break;
                }
            }
            if(isValid) {
                c[i].push_back(j);
            }
        }
    }
    map<int, int> mp;
    vector<int> scc = findSCC(n, c);
    int ans = n;
    for(int i = 0; i < n; i++){
        if(mp.find(scc[i]) == mp.end()) {
            mp.insert({scc[i], 0});
        }
        mp.find(scc[i]) -> second ++;
        ans = min(ans, n - mp.find(scc[i]) -> second);
    }
    cout << ans << "\n";
    
    return 0;
}
