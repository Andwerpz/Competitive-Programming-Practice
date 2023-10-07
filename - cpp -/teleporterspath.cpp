#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//CSES - 1693

//the goal is to find an eulerian path starting at node 1 and ending at node n. 

//idk why this works, but i'll outline what i did here. 

//first, i just ran the eulerian cycle algorithm on the graph, starting at 1, regardless of whether there is one or not. 
//then, if there are less than m + 1 entries in the generated path, then there cannot be an eulerian path or cycle
//if the last entry is not n, then we don't end at node n. 
//finally, check that there are no repeated edges.

//if all checks are satisfied, it is a valid eulerian path starting at 1 and ending at n. 

void euler_path(vector<vector<int>>& c, vector<int>& ptr, vector<int>& ans, int i) {
    while(ptr[i] < c[i].size()) {
        int next = c[i][ptr[i] ++];
        euler_path(c, ptr, ans, next);
    }
    ans.push_back(i);
}

//an euler tour only exists if the degrees of all vertices are even
//an euler path only exists if the number of vertices with odd degrees are two, or zero, in which case an euler cycle exists. 
//and of course, the graph is sufficiently connected. 

//this function doesn't check any of those. TODO make it do that
vector<int> euler_path(vector<vector<int>>& c, int i) {
    int n = c.size();
    vector<int> ptr(n, 0);
    vector<int> ans(0);
    euler_path(c, ptr, ans, i);
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<vector<int>> c(n, vector<int>(0));
    set<pair<int, int>> edges;
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        a --;
        b --;
        c[a].push_back(b);
        edges.insert({a, b});
    }
    vector<int> path = euler_path(c, 0);
    bool isValid = true;
    if(path.size() != m + 1) {
        isValid = false;
    }
    reverse(path.begin(), path.end());
    if(path.back() != n - 1) {
        isValid = false;
    }
    for(int i = 1; i < path.size(); i++){
        if(edges.find({path[i - 1], path[i]}) == edges.end()) {
            isValid = false;
        }
        edges.erase({path[i - 1], path[i]});
    }
    if(!isValid) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    for(int i = 0; i < path.size(); i++){
        cout << path[i] + 1 << " ";
    }
    cout << "\n";
    
    return 0;
}
