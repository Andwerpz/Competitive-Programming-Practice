
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//CSES 1668

//since have two teams, and nobody on the same team can be friends, a simple bipartiteness check will do. 

//if the graph is bipartite, and you put all people of one color into one team, and the other color into
//the other team, then according to the definition of bipartiteness, people of the same color will never
//be friends, which satisfies our requirements. 

//if the graph is not bipartite, then it will never work. 

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
    vector<int> color(n);
    bool isValid = true;
    for(int i = 0; i < n; i++){
        if(color[i] != 0){
            continue;
        }
        queue<int> q;
        q.push(i);
        color[i] = 1;
        while(q.size() != 0){
            int cur = q.front();
            int curColor = color[cur];
            q.pop();
            for(int j : c[cur]){
                if(color[j] != 0){
                    if(color[j] == color[cur]){
                        isValid = false;
                        goto outer;
                    }
                    continue;
                }
                color[j] = curColor == 1? 2 : 1;
                q.push(j);
            }
        } 
    }
    outer:;
    if(!isValid){
        cout << "IMPOSSIBLE\n";
    }
    else {
        for(int i : color){
            cout << i << " ";
        }
        cout << endl;
    }
    
    return 0;
}
