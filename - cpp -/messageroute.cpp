
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//CSES 1667

//do a backtrack from the nth computer to the 1st computer.

//for each computer, save which is the next computer to get back to the nth computer. Using this, 
//we can reconstruct the path from the 1st to the nth computer. 

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
    vector<int> backtrack(n);   //which node should i go to to get back to the nth node
    vector<bool> v(n);
    queue<int> q;
    v[n - 1] = true;
    q.push(n - 1);
    while(q.size() != 0){
        int cur = q.front();
        q.pop();
        for(int i : c[cur]){
            if(v[i]){
                continue;
            }
            v[i] = true;
            backtrack[i] = cur;
            q.push(i);
        }
    }
    if(!v[0]){
        cout << "IMPOSSIBLE\n";
    }
    else{
        vector<int> ans;
        int cur = 0;
        while(true){
            ans.push_back(cur + 1);
            if(cur + 1 == n){
                break;
            }
            cur = backtrack[cur];
        }
        cout << ans.size() << endl;
        for(int i = 0; i < ans.size(); i++){
            cout << ans[i] << " ";
        }
        cout << endl;
    }
    
    return 0;
}
