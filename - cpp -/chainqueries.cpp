#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

void insert(map<int, int>& m, int val) {
    m[val] ++;
}

void erase(map<int, int>& m, int val) {
    m[val] --;
    if(m[val] == 0){
        m.erase(m.find(val));
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, q;
        cin >> n >> q;
        vector<bool> is_black(n, false);
        for(int i = 0; i < n; i++){
            int next;
            cin >> next;
            is_black[i] = next;
        }
        vector<vector<int>> c(n);
        for(int i = 0; i < n - 1; i++){
            int x, y;
            cin >> x >> y;
            x --;
            y --;
            c[x].push_back(y);
            c[y].push_back(x);
        }
        vector<bool> is_heavy(n, false);
        for(int i = 0; i < n; i++){
            if(c[i].size() >= sqrt(n)) {
                is_heavy[i] = true;
            }
        }
        vector<vector<int>> ch(n);
        for(int i = 0; i < n; i++){
            if(!is_heavy[i]) {
                continue;
            }
            for(int j = 0; j < c[i].size(); j++){
                int next = c[i][j];
                if(next < i) {
                    continue;
                }
                ch[next].push_back(i);
                ch[i].push_back(next);
            }
        }
        //create initial graph state
        map<int, int> m;
        vector<int> bn_cnt(n, 0);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < c[i].size(); j++){
                int next = c[i][j];
                bn_cnt[i] += is_black[next];
            }
            insert(m, bn_cnt[i]);
        }
        //handle queries
        for(int i = 0; i < q; i++){
            int x;
            cin >> x;
            x --;
        }
    }
    
    return 0;
}