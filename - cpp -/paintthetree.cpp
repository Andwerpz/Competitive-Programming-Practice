#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1975D

//since piece b cannot do anything without piece a, it's optimal to first get piece a and b together. Then, you just have
//to move them both through an euler tour of the tree, rooted at where they first met. 

//note that we don't have to do a complete tour, as we just have to color all of the nodes. Therefore, we want our ending
//node to have the largest distance possible to the root, so we can subtract off that distance from the tour distance. 

int calc_dist(int cur, int p, vector<vector<int>>& c, vector<int>& dist, vector<int>& max_subt_dist) {
    max_subt_dist[cur] = 0;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p){
            continue;
        }
        dist[next] = dist[cur] + 1;
        max_subt_dist[cur] = max(max_subt_dist[cur], calc_dist(next, cur, c, dist, max_subt_dist) + 1);
    }
    return max_subt_dist[cur];
}

bool calc_contain_b(int cur, int p, vector<vector<int>>& c, vector<bool>& subt_cont_b, int b) {
    if(cur == b) {
        subt_cont_b[cur] = true;
    }
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p){
            continue;
        }
        subt_cont_b[cur] = subt_cont_b[cur] || calc_contain_b(next, cur, c, subt_cont_b, b);
    }
    return subt_cont_b[cur];
}

int calc_max_dist(int cur, int p, vector<vector<int>>& c) {
    int ans = 0;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p){
            continue;
        }
        ans = max(ans, calc_max_dist(next, cur, c) + 1);
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
        int a, b;
        cin >> a >> b;
        a --;
        b --;
        vector<vector<int>> c(n);
        for(int i = 0; i < n - 1; i++){
            int x, y;
            cin >> x >> y;
            x --;
            y --;
            c[x].push_back(y);
            c[y].push_back(x);
        }
        //root the tree at a
        vector<int> dist(n, -1);
        vector<int> max_subt_dist(n, -1);
        dist[a] = 0;
        calc_dist(a, -1, c, dist, max_subt_dist);
        vector<bool> subt_cont_b(n, false);
        calc_contain_b(a, -1, c, subt_cont_b, b);
        //find the node where they meet
        int ptr_p = -1;
        int ptr = a;
        int b_dist = dist[b];
        int ans = 0;
        while(b_dist >= 2) {
            for(int i = 0; i < c[ptr].size(); i++){
                int next = c[ptr][i];
                if(next == ptr_p) {
                    continue;
                }
                if(subt_cont_b[next]) {
                    ptr_p = ptr;
                    ptr = next;
                    b_dist -= 2;
                    ans ++;
                    break;
                }
            }
        }
        ans += 2 * (n - 1) + b_dist - calc_max_dist(ptr, -1, c);
        cout << ans << "\n";
    }
    
    return 0;
}