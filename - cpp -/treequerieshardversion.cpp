#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//Codeforces - 1695D2

//first, try to analyze in the case where the tree doesn't have any 'chains'. We define a chain to be
//any node with a degree of exactly 2. 

//In that case, we can identify any node that is adjacent to at most one non-leaf node. We need to query exactly k - 1 
//of those leaf nodes, if there are k leaf nodes that it's adjacent to. Then, we can just cut off all the leaf nodes, as they
//don't matter anymore. 

//now, notice that it's as if we queried from the node that we've identified. Continue this process until there is only leaf
//nodes left. 

//I claim that chains will not change the answer. Compress the tree before running this algorithm. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<set<int>> c(n);
        for(int i = 0; i < n - 1; i++){
            int a, b;
            cin >> a >> b;
            a --;
            b --;
            c[a].insert(b);
            c[b].insert(a);
        }
        int nr_edge = n - 1;
        for(int i = 0; i < n; i++){
            if(c[i].size() != 2){
                continue;
            }
            nr_edge --;
            int a = *c[i].begin();
            int b = *c[i].rbegin();
            c[a].erase(c[a].find(i));
            c[b].erase(c[b].find(i));
            c[a].insert(b);
            c[b].insert(a);
        }
        if(nr_edge == 1){
            cout << "1\n";
            continue;
        }
        queue<int> q;
        vector<bool> v(n, false);
        for(int i = 0; i < n; i++){
            if(c[i].size() == 1){
                q.push(i);
                v[i] = true;
            }
        }
        vector<bool> is_child(n, false);
        int ans = 0;
        while(q.size() != 0){
            int cur = q.front();
            q.pop();
            vector<int> children(0);
            int nr_q = 0;
            for(auto i = c[cur].begin(); i != c[cur].end(); i++){
                int next = *i;
                if(is_child[next]) {
                    children.push_back(next);
                    nr_q += c[next].size() != 1;
                }
                else {
                    if(!v[next]) {
                        v[next] = true;
                        q.push(next);
                    }
                }
            }
            for(int i = 0; i < children.size(); i++){
                int next = children[i];
                if(c[next].size() == 1 && nr_q != children.size() - 1) {
                    ans ++;
                    nr_q ++;
                }
            }
            is_child[cur] = true;
        }
        cout << ans << "\n";
    }
    
    return 0;
}