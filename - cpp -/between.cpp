#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1815C

//note that if we can place down as many 1s as we want, then all sequences could be infinite. 

//for each pair, (a[i], b[i]), we can say that a[i] depends on b[i]. The maximum amount of 
//occurrences of a[i] is equal to the minimum amount of occurrences of the dependencies of a[i], + 1. 

//to find the maximum amount of occurrences for each a[i], we can do a bfs starting from 1. 

//if the bfs starting from 1 doesn't visit some nodes, then the sequence can be infinite. 
//otherwise, we can construct the finite sequence of maximum length. 

//denote 'x' as the maximum maximum ocurrences among all a[i]. Note that it has to be the case that there are elements in
//a with maximum occurrences from 1 to x. 

//denote g[j] as the list of a[i] with maximum occurrences equal to j. 

//we will append to the answer the lists in g in this order:
//g[x], 
//g[x - 1], g[x], 
//g[x - 2], g[x - 1], g[x]
// ... 
//g[1], g[2], ... g[x]

//the relative order of elements in the lists g[j] doesn't matter. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        int n, m;
        cin >> n >> m;
        vector<int> d(n, -1);
        d[0] = 0;
        vector<vector<int>> c(n, vector<int>(0));
        for(int i = 0; i < m; i++){
            int a, b;
            cin >> a >> b;
            a --;
            b --;
            c[b].push_back(a);
        } 
        queue<int> q;
        q.push(0);
        while(q.size() != 0){
            int cur = q.front();
            q.pop();
            for(int i = 0; i < c[cur].size(); i++){
                int next = c[cur][i];
                if(d[next] == -1){
                    d[next] = d[cur] + 1;
                    q.push(next);
                }
            }
        }
        bool infinite = false;
        vector<vector<int>> g(0);
        for(int i = 0; i < d.size(); i++){
            int ng = d[i];
            if(ng == -1){
                infinite = true;
                break;
            }
            while(g.size() <= ng) {
                g.push_back(vector<int>(0));
            }
            g[ng].push_back(i + 1);
        }
        if(infinite) {
            cout << "INFINITE\n";
            continue;
        }
        cout << "FINITE\n";
        vector<int> ans(0);
        for(int i = g.size() - 1; i >= 0; i--){
            for(int j = i; j < g.size(); j++){
                for(int k = 0; k < g[j].size(); k++){
                    ans.push_back(g[j][k]);
                }
            }
        }
        cout << ans.size() << "\n";
        for(int i = 0; i < ans.size(); i++){
            cout << ans[i] << " \n"[i == ans.size() - 1];
        }
    }
    
    return 0;
}
