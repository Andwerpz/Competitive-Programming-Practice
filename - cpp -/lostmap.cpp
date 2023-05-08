#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 13 H

//sort edges from least to greatest, and construct the minimum spanning tree. 

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
    
    dsu_init();
    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(n, 0));
    priority_queue<vector<int>> s;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> a[i][j];
            if(i <= j){
                continue;
            }
            s.push({-a[i][j], i + 1, j + 1});
        }
    }
    for(int i = 0; i < n - 1; i += 0){
        vector<int> next = s.top();
        s.pop();
        int u = next[1];
        int v = next[2];
        if(find(u) == find(v)) {
            continue;
        }
        i ++;
        cout << next[1] << " " << next[2] << "\n";
        unify(u, v);
    }
    
    return 0;
}
