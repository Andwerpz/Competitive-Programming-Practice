#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//USACO 2023 December Contest, Gold P2

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, ll>>> c(n, vector<pair<int, ll>>(0));   //{node, label}
    vector<vector<int>> c_rev(n, vector<int>(0));
    vector<int> od(n, 0);
    for(int i = 0; i < m; i++){
        int a, b, l;
        cin >> a >> b >> l;
        a --;
        b --;
        c[a].push_back({b, l});
        c_rev[b].push_back(a);
        od[a] ++;
    }
    vector<pair<int, pair<int, ll>>> ans(n);    //{which child, {length, label sum}}
    queue<int> q;
    for(int i = 0; i < n; i++){
        if(od[i] == 0){
            q.push(i);
        }
    }
    while(q.size() != 0){
        int cur = q.front();
        q.pop();
        int ind = -1;
        int length = 0;
        ll label = 1e18;
        ll label_sum = 0;
        for(int i = 0; i < c[cur].size(); i++){
            int next = c[cur][i].first;
            ll next_label = c[cur][i].second;
            ll next_label_sum = ans[next].second.second;
            int next_length = ans[next].second.first;
            if(next_length + 1 > length) {
                ind = i;
                length = next_length + 1;
                label = next_label;
                label_sum = next_label_sum + next_label;
                continue;
            }
            if(next_length + 1 == length) {
                if(next_label < label) {
                    label = next_label;
                    label_sum = next_label_sum + next_label;
                    ind = i;
                }
                else if(n <= 5000) {
                    int pa = c[cur][ind].first;
                    int pb = next;
                    bool better = false;
                    while(true) {
                        if(c[pa].size() == 0){
                            break;
                        }
                        int pa_ind = ans[pa].first;
                        int pb_ind = ans[pb].first;
                        if(c[pa][pa_ind].second != c[pb][pb_ind].second){
                            better = c[pa][pa_ind].second > c[pb][pb_ind].second;
                            break;
                        }
                        pa = c[pa][pa_ind].first;
                        pb = c[pb][pb_ind].first;
                    }
                    if(better) {
                        label = next_label;
                        label_sum = next_label_sum + next_label;
                        ind = i;
                    }
                }
            }
        }
        for(int i = 0; i < c_rev[cur].size(); i++){
            int next = c_rev[cur][i];
            od[next] --;
            if(od[next] == 0){
                q.push(next);
            }
        }
        ans[cur] = {ind, {length, label_sum}};
    }
    for(int i = 0; i < n; i++){
        cout << ans[i].second.first << " " << ans[i].second.second << "\n";
    }
    
    return 0;
}
