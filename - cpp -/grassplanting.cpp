
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//USACO Silver 2019 January

//since there are n nodes and n - 1 edges, and the graph is fully connected, we know that 
//the graph has to be a tree structure. 

//Colors don't need to just not be adjacent, they can't be 2 away from each other. 

//the answer is the maximum connections to a node + 1. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("planting.in", "r", stdin);
    freopen("planting.out", "w", stdout);
    
    int n;
    cin >> n;
    int ans = 0;
    vector<int> c(n);
    for(int i = 0; i < n - 1; i++){
        int a, b;
        cin >> a >> b;
        a --;
        b --;
        c[a] ++;
        c[b] ++;
    }
    for(int i : c){
        ans = max(ans, i + 1);
    }
    cout << ans << endl;
    
    return 0;
}
