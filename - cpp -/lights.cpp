#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1907G

//let's convert the problem into a graph problem. 
//n nodes, indexed from 0 to n - 1. Each node i has an outgoing edge to another node given 
//by a[i]. 

//Then, the graph formed is such that each connected component has exactly 1 cycle. 
//we can start by considering all nodes that have indegree 0; if they are on, then 
//switch them off and remove them from the graph, if they are not on, just remove them
//from the graph. 

//After removing all the nodes we can, we are left with a bunch of cycles. If a cycle
//has an odd amount of on nodes, then it's impossible to turn them all off. Otherwise, there 
//is always a way. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        string light_str;
        cin >> light_str;
        vector<bool> on(n);
        for(int i = 0; i < n; i++){
            on[i] = light_str[i] == '1';
        }
        vector<int> c(n);
        for(int i = 0; i < n; i++){
            cin >> c[i];
            c[i] --;
        }
        vector<int> indeg(n, 0);
        for(int i = 0; i < n; i++){
            indeg[c[i]] ++;
        }
        vector<bool> v(n, false);
        queue<int> q;
        for(int i = 0; i < n; i++){
            if(indeg[i] == 0){
                q.push(i);
            }
        }
        vector<int> ans(0);
        while(q.size() != 0){
            int cur = q.front();
            q.pop();
            v[cur] = true;
            if(on[cur]) {
                on[cur] = false;
                on[c[cur]] = !on[c[cur]];
                ans.push_back(cur);
            }
            indeg[c[cur]] --;
            if(indeg[c[cur]] == 0){
                q.push(c[cur]);
            }
        }
        bool is_valid = true;
        for(int i = 0; i < n; i++){
            if(v[i]) {
                continue;
            }
            int ptr = c[i];
            v[i] = true;
            vector<int> loop(1, i);
            int nr_on = on[i];
            while(ptr != i){
                v[ptr] = true;
                nr_on += on[ptr];
                loop.push_back(ptr);
                ptr = c[ptr];
            }
            if(nr_on % 2 == 1){
                is_valid = false;
                break;
            }
            int cnt = 0;
            vector<bool> use(loop.size(), false);
            for(int j = 0; j < loop.size(); j++){
                int next = loop[j];
                //cout << next << " " << on[next] << "\n";
                if(on[next]) {
                    on[next] = false;
                    on[c[next]] = !on[c[next]];
                    use[j] = true;
                    cnt ++;
                }
            }
            //cout << "CNT : " << cnt << "\n";
            if(loop.size() - cnt < cnt) {
                cnt = loop.size() - cnt;
                for(int j = 0; j < loop.size(); j++){
                    use[j] = !use[j];
                }
            }
            for(int j = 0; j < use.size(); j++){
                if(use[j]){
                    ans.push_back(loop[j]);
                }
            }
        }
        if(!is_valid) {
            cout << "-1\n";
        }
        else {
            cout << ans.size() << "\n";
            for(int i = 0; i < ans.size(); i++){
                cout << (ans[i] + 1) << " \n"[i == ans.size() - 1];
            }
        }
    }
    
    return 0;
}
