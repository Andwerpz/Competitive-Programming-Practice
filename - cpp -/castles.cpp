#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2010 D

//{num required, num returning}
pair<int, int> calc(int cur, int parent, vector<int>& req, vector<int>& die, vector<vector<int>>& c) {
    int cur_req = 0;
    int cur_soldiers = 0;
    vector<pair<int, int>> child(0);
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == parent) {
            continue;
        }
        child.push_back(calc(next, cur, req, die, c));
    }
    sort(child.begin(), child.end(), [](pair<int, int>& a, pair<int, int>& b) -> bool {
        return a.second > b.second;
    });
    cur_req = req[cur];
    cur_soldiers = cur_req - die[cur];
    for(int i = 0; i < child.size(); i++){
        if(child[i].first > cur_soldiers) {
            int diff = child[i].first - cur_soldiers;
            cur_soldiers += diff;
            cur_req += diff;
        }
        //conquer the branch
        cur_soldiers -= child[i].first;
        cur_soldiers += child[i].second;
    }
    return {cur_req, cur_soldiers};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    int caseno = 0;
    while(n != 0){
        caseno ++;
        cout << "Case " << caseno << ": ";
        vector<int> req(n, 0);
        vector<int> die(n, 0);
        for(int i = 0; i < n; i++){
            int a, m, g;
            cin >> a >> m >> g;
            die[i] = m + g;
            req[i] = max(a, die[i]);
        }
        vector<vector<int>> c(n, vector<int>(0));
        for(int i = 0; i < n - 1; i++){
            int a, b;
            cin >> a >> b;
            a --;
            b --;
            c[a].push_back(b);
            c[b].push_back(a);
        }
        int ans = 1e9;
        for(int i = 0; i < n; i++){
            //root at node i
            ans = min(ans, calc(i, -1, req, die, c).first);
        }
        cout << ans << "\n";
        cin >> n;
    }
    
    return 0;
}
