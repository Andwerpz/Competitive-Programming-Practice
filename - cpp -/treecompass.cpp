#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1943C

//one idea is to find the node with the minimum distance to all other nodes, and just paint concentric rings around
//that node. This works in the case when the diameter of the tree is odd. 

//if the diameter is even, then we'll waste one move at the beginning by only coloring one node. Is there a way where we
//can color at least 2 nodes on the diameter on every move?

//There is in fact a way. Consider a bipartite coloring of the tree (red, blue). We can pick a red node on the diameter,
//and with odd distances, color 2 blue nodes. Likewise for the blue nodes. Thus, the solution is to pick
//the red and blue nodes with the minimum distance to all the blue and red nodes repsectively. Then, we can 
//guarantee that the number of operations is equal to ceil(diameter length / 2). 

void color_tree(int cur, int p, vector<vector<int>>& c, vector<int>& color) {
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p){
            continue;
        }
        color[next] = -color[cur];
        color_tree(next, cur, c, color);
    }
}

int max_dist(int cur, int p, vector<vector<int>>& c, int dist, vector<int>& color, int _color) {
    int ans = color[cur] == _color? dist : -1;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p){
            continue;
        }
        ans = max(max_dist(next, cur, c, dist + 1, color, _color), ans);
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<vector<int>> c(n, vector<int>());
        for(int i = 0; i < n - 1; i++){
            int u, v;
            cin >> u >> v;
            u --;
            v --;
            c[u].push_back(v);
            c[v].push_back(u);
        }
        if(n == 1){
            cout << "1\n";
            cout << "1 0\n";
            continue;
        }
        vector<int> color(n, 0);
        color[0] = 1;
        color_tree(0, -1, c, color);
        int r_min = 1e9;
        int b_min = 1e9;
        int r_node = -1;
        int b_node = -1;
        for(int i = 0; i < n; i++){
            int c_max = max_dist(i, -1, c, 0, color, -color[i]);
            if(c_max == -1){
                continue;
            }
            if(color[i] == -1){
                if(c_max < r_min) {
                    r_min = c_max;
                    r_node = i;
                }
            }
            else {
                if(c_max < b_min) {
                    b_min = c_max;
                    b_node = i;
                }
            }
        }
        int ops = 0;
        if(r_node != -1){
            ops += (r_min + 1) / 2;
        }
        if(b_node != -1){
            ops += (b_min + 1) / 2;
        }
        cout << ops << "\n";
        if(r_node != -1){
            for(int i = 1; i <= r_min; i += 2){
                cout << r_node + 1 << " " << i << "\n";
            }
        }
        if(b_node != -1){
            for(int i = 1; i <= b_min; i += 2){
                cout << b_node + 1 << " " << i << "\n";
            }
        }
    }
    
    return 0;
}
