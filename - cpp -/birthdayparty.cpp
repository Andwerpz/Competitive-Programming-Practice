#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 09 B

//if there exists a bridge in the graph, then by definition, removing it will disconnect the graph. 

int ptr;
vector<int> p;

void art(vector<vector<int>>& c, vector<int>& res, vector<bool>& v, int cur, int parent) {
    //cout << "CUR : " << cur << " " << ptr << "\n";
    p[cur] = parent;
    res[cur] = ptr;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == parent) {
            continue;
        }
        if(!v[next]) {
            v[next] = true;
            ptr ++;
            art(c, res, v, next, cur);
        }
        res[cur] = min(res[next], res[cur]);
        //cout << "BACK : " << cur << " " << next << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    while(n != 0){
        int m;
        cin >> m;
        vector<vector<int>> c(n + 1, vector<int>(0));
        for(int i = 0; i < m; i++){
            int a, b;
            cin >> a >> b;
            c[a].push_back(b);
            c[b].push_back(a);
        }
        c[n].push_back(0);
        c[0].push_back(n);
        vector<bool> v(n + 1, false);
        v[n] = true;
        vector<int> res(n + 1, 0);
        ptr = 0;
        p = vector<int>(n + 1, -1);
        art(c, res, v, n, -1);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < c[i].size(); j++){
                int next = c[i][j];
                if(next == p[i]){
                    continue;
                }
                res[i] = min(res[i], res[next]);
            }
        }
        // for(int i = 0; i < n; i++){
        //     cout << res[i] << " ";
        // }
        // cout << "\n";
        bool isValid = false;
        for(int i = 0; i < n; i++){
            if(res[i] != 1){
                isValid = true;
            }
        }
        cout << (isValid? "Yes\n" : "No\n");
        cin >> n;
    }
    
    return 0;
}
