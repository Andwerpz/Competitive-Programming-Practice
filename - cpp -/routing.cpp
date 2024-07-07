#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1804E

//notice that if we can find a cycle where all the nodes are either on the cycle, or directly adjacent
//to the cycle, we can just create the cycle and it will allow any node to get to any other node. 

//we can use dp to find all possible cycles in the graph. dp[i][j] = is this a valid cycle given
//i is a bitmask describing what nodes are in the cycle
//j is the last node in the path, the first node in the bitmask is the first node in the path. 

//once we've found all cycles, we can just test each one of them to see if they follow the above criteria. 

//final complexity is 2^n * n^2. 

bool dp[(1 << 20)][20];
int p[(1 << 20)][20];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector c(n, vector<int>(0));
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        u --;
        v --;
        c[u].push_back(v);
        c[v].push_back(u);
    }
    for(int i = 0; i < (1 << n); i++){
        for(int j = 0; j < n; j++){
            dp[i][j] = false;
            p[i][j] = -1;
        }
    }
    for(int i = 0; i < n; i++){
        //i is the starting node, we are not allowed to go to any node less than i
        p[(1 << i)][i] = -2;
        queue<pair<int, int>> q;
        q.push({(1 << i), i});
        while(q.size() != 0){
            int bits = q.front().first;
            int cur = q.front().second;
            q.pop();
            bool is_cycle = false;
            for(int j = 0; j < c[cur].size(); j++){
                int next = c[cur][j];
                if(next == i){
                    is_cycle = true;
                }
                if(next <= i) {
                    continue;
                }
                if(bits & (1 << next)) {
                    continue;
                }
                int nmask = bits | (1 << next);
                if(p[nmask][next] == -1) {
                    p[nmask][next] = cur;
                    q.push({nmask, next});
                }
            }
            if(is_cycle){
                // cout << "CYCLE : " << cur << " " << i << endl;
                dp[bits][cur] = true;
            }
        }
    }
    //look for a cycle that is valid. 
    int vmask = -1;
    int sptr = -1;
    for(int i = 0; i < (1 << n); i++){
        bool found_valid = false;
        for(int j = 0; j < n; j++){
            if(dp[i][j]) {
                found_valid = true;
                sptr = j;
            }
        }
        if(!found_valid) {
            continue;
        }
        // cout << "FOUND VALID : " << i << "\n";
        bool is_valid = true;
        for(int j = 0; j < n; j++){
            if(i & (1 << j)) {
                continue;
            }
            bool c_valid = false;
            for(int k = 0; k < c[j].size(); k++){
                int next = c[j][k];
                if(i & (1 << next)) {
                    c_valid = true;
                }
            }
            if(!c_valid) {
                // cout << "NOT VALID : " << j << "\n";
                is_valid = false;
            }
        }
        if(is_valid) {
            vmask = i;
            break;
        }
    }
    // cout << "VMASK : " << vmask << endl;
    if(vmask == -1){
        cout << "NO\n";
        return 0;
    }
    //use valid mask to construct cycle. 
    vector<int> ans(n, -1);
    for(int i = 0; i < n; i++){
        if(vmask & (1 << i)) {
            continue;
        }
        for(int j = 0; j < c[i].size(); j++){
            int next = c[i][j];
            if(vmask & (1 << next)) {
                ans[i] = next;
                break;
            }
        }
    }
    int ptr = sptr;
    while(true) {
        // cout << "PTR : " << ptr << endl;
        if(p[vmask][ptr] == -2){
            ans[sptr] = ptr;
            break;
        }
        int nptr = p[vmask][ptr];
        ans[nptr] = ptr;
        vmask ^= (1 << ptr);
        ptr = nptr;
    }
    cout << "YES\n";
    for(int i = 0; i < n; i++){
        cout << ans[i] + 1 << " \n"[i == n - 1];
    }
    
    return 0;
}