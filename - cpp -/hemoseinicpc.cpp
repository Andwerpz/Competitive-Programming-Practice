#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1592D

//first, we can notice that there must exist a path of length 1 with maximum gcd. This is because the gcd of a 
//path will only decrease as the path length grows. 

//the second idea is to just not care about the tree structure, and do binary search over the edge list. 
//Since we know that the maximum gcd just has to be equal to the maximum edge weight, we just need to find the
//edge with the maximum weight. 

//but not caring about the tree structure has it's downfalls, as if we naively query the nodes connected to the
//edges we're interested in, we might accidentally include another edge that we didn't mean to. 

//To fix this, we need to ensure all the nodes that we query over form a connected component. We can easily do 
//this by just doing BFS until half of the edges still in consideration are in our connected component. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<pair<int, int>> clist(0);
    vector<vector<pair<int, int>>> c(n, vector<pair<int, int>>(0));
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        u --;
        v --;
        clist.push_back({u, v});
        c[u].push_back({v, i});
        c[v].push_back({u, i});
    }
    cout << "? " << n << " ";
    for(int i = 1; i <= n; i++){
        cout << i << " ";
    }
    cout << endl;
    int maxg;
    cin >> maxg;
    int in_cnt = n - 1;
    vector<bool> in(n - 1, true);
    while(in_cnt != 1){
        //bfs from 1 until we get in_cnt / 2 edges that are in
        vector<bool> v(n, false);
        vector<bool> c_in(n - 1, false);
        queue<int> q;
        q.push(0);
        v[0] = true;
        int c_in_cnt = 0;
        while(q.size() != 0){
            int cur = q.front();
            q.pop();
            for(int i = 0; i < c[cur].size() && c_in_cnt < in_cnt / 2; i++){
                int eind = c[cur][i].second;
                int next = c[cur][i].first;
                if(!v[next]) {
                    if(in[eind]) {
                        c_in[eind] = true;
                        c_in_cnt ++;
                    }
                    v[next] = true;
                    q.push(next);
                }
            }
        }
        vector<int> qlist(0);
        for(int i = 0; i < v.size(); i++){
            if(v[i]){
                qlist.push_back(i);
            }
        }
        cout << "? " << qlist.size() << " ";
        for(int i = 0; i < qlist.size(); i++){
            cout << qlist[i] + 1 << " ";
        }
        cout << endl;
        int g;
        cin >> g;
        if(g == maxg) {
            for(int i = 0; i < n - 1; i++){
                if(in[i] && !c_in[i]) {
                    in[i] = false;
                    in_cnt --;
                }
            }
        }
        else {
            for(int i = 0; i < n - 1; i++){
                if(in[i] && c_in[i]) {
                    in[i] = false;
                    in_cnt --;
                }
            }
        }
    }
    int eans = -1;
    for(int i = 0; i < in.size(); i++){
        if(in[i]){
            eans = i;
        }
    }
    cout << "! " << clist[eans].first + 1 << " " << clist[eans].second + 1 << "\n";
    
    return 0;
}
