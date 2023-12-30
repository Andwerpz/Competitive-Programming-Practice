#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ACPC 2023 Fall Contest E

//note that it's never needed to command a pose twice. So the problem lies in finding the correct order
//of poses to command. 

//note that some poses should always be commanded before other poses; if a pose 'covers' a location that
//another pose is supposed to end up with, the first pose should be called first. 

//then, we just need to find if there exists a topological ordering for this directed graph. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
        a[i] --;
    }
    vector<bool> satisfy(n, false);
    vector<vector<int>> c(m, vector<int>(0));
    for(int i = 0; i < m; i++){
        int b;
        cin >> b;
        char sep;
        cin >> sep;
        for(int j = 0; j < b; j++){
            int next;
            cin >> next;
            next --;
            if(a[next] != i) {
                c[i].push_back(a[next]);
            }
            else {
                satisfy[next] = true;
            }
        }
    }
    bool is_valid = true;
    queue<int> q;
    vector<int> in(m, 0);
    vector<bool> v(m, false);
    for(int i = 0; i < m; i++){
        for(int j = 0; j < c[i].size(); j++){
            in[c[i][j]] ++;
        }
    }
    for(int i = 0; i < m; i++){
        if(in[i] == 0){
            q.push(i);
            v[i] = true;
        }
    }
    while(q.size() != 0){
        int cur = q.front();
        q.pop();
        for(int i = 0; i < c[cur].size(); i++){
            int next = c[cur][i];
            in[next] --;
            if(in[next] == 0){
                q.push(next);
                v[next] = true;
            }
        }
    }
    for(int i = 0; i < m; i++){
        if(!v[i]) {
            is_valid = false;
            break;
        }
    }
    for(int i = 0; i < n; i++){
        if(!satisfy[i]) {
            is_valid = false;
            break;
        }
    }
    cout << (is_valid? "YES" : "NO") << "\n";
    
    return 0;
}
