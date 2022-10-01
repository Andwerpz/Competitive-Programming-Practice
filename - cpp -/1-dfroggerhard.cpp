#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//MAPS 2022 B

//too much mem, but right approach. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    vector<vector<int>> c(n, vector<int>(0));
    vector<bool> isStart(n, false);
    vector<bool> v(n);
    vector<set<int>> u(n, set<int>());
    for(int i = 0; i < n; i++){
        if(i + a[i] < n && i + a[i] >= 0){
            c[i + a[i]].push_back(i);
        }
        if(v[i]){
            continue;
        }
        vector<int> path(1);
        set<int> pathSet;
        pathSet.insert(i);
        path[0] = i;
        v[i] = true;
        int cur = i + a[i];
        while(cur >= 0 && cur < n && cur != path[0] && !v[cur]){
            pathSet.insert(cur);
            path.push_back(cur);
            v[cur] = true;
            cur += a[cur];
        }
        if(cur < 0 || cur >= n){    //falls off board
            int last = *path.rbegin();
            isStart[last] = true;
            set<int> unique;
            unique.insert(a[last]);
            u[last] = unique;
        }
        else if(pathSet.find(cur) != pathSet.end()){  //cycle
            vector<int> cycle(0);
            set<int> unique;
            for(int j = path.size() - 1; j >= 0; j--){
                unique.insert(a[path[j]]);
                cycle.push_back(path[j]);
                if(path[j] == cur){
                    break;
                }
            }
            for(int j : cycle){
                isStart[j] = true;
                u[j] = unique;
            }
        }
    }
    for(int i = 0; i < n; i++){
        if(!isStart[i]){
            continue;
        }
        stack<int> s;
        s.push(i);
        while(s.size() != 0){
            int next = s.top();
            s.pop();
            set<int> unique = u[next];
            for(int j : c[next]){
                if(isStart[j]){
                    continue;
                }
                for(int k : unique){
                    u[j].insert(k);
                }
                u[j].insert(a[j]);
                s.push(j);
            }
        }
    }
    ll ans = 0;
    for(set<int> i : u){
        ans += (ll) i.size();
    }
    cout << ans << "\n";
    
    return 0;
}
