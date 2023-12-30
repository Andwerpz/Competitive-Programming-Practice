#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1895E

//if monocarp puts out a card, then it is always optimal for bicarp to put out the card with the 
//highest defense that beats it. 

//since the state of the game can be completely described as who's turn it is and what card is currently out, 
//and for each state, there is only 1 optimal move, if there is one, we can treat this as a directed graph problem,
//where each node is a game state, and each edge is the optimal move for that state. 

//from here, we can easily see that loops are situations where the game goes on indefinitely, and when a state doesn't
//have a move, then one person will win. The outcome of a state is just the terminal node when following the path of 
//optimal moves. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<pair<int, int>> a(n);    //{attack, defense}
        for(int i = 0; i < n; i++){
            cin >> a[i].first;
        }
        for(int i = 0; i < n; i++){
            cin >> a[i].second;
        }  
        int m;
        cin >> m;
        vector<pair<int, int>> b(m);    //{attack, defense};
        for(int i = 0; i < m; i++){
            cin >> b[i].first;
        }
        for(int i = 0; i < m; i++){
            cin >> b[i].second;
        }
        int ptr = 0;
        vector<int> a_id(n), b_id(m);
        for(int i = 0; i < n; i++){
            a_id[i] = ptr++;
        }
        for(int i = 0; i < m; i++){
            b_id[i] = ptr++;
        }
        vector<int> c(ptr, -1); //-1 means no edge
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        //construct lookup maps to construct graph
        map<int, pair<int, int>> a_m, b_m;  //{attack, {best defense, node id}}
        int best_def = -1;
        for(int i = 0; i < n; i++){
            if(a[i].second > best_def) {
                best_def = a[i].second;
                a_m.insert({a[i].first, {best_def, a_id[i]}});
            }
        }
        best_def = -1;
        for(int i = 0; i < m; i++){
            if(b[i].second > best_def) {
                best_def = b[i].second;
                b_m.insert({b[i].first, {best_def, b_id[i]}});
            }
        }
        //construct graph
        for(int i = 0; i < n; i++){
            int def = a[i].second;
            if(b_m.rbegin() -> first <= def) {
                //bicarp doesn't have a card that can beat this one
                continue;
            }
            auto j = b_m.upper_bound(def);
            c[a_id[i]] = j -> second.second;
        }
        for(int i = 0; i < m; i++){
            int def = b[i].second;
            if(a_m.rbegin() -> first <= def) {
                //monocarp doesn't have a card that can beat this one
                continue;
            }
            auto j = a_m.upper_bound(def);
            c[b_id[i]] = j -> second.second;
        }
        //find loops and stuff
        vector<int> win(ptr, -1);   //0 : tie, 1: monocarp, 2: bicarp
        vector<bool> v(ptr, false);
        for(int i = 0; i < n; i++){
            if(v[i]){
                continue;
            }
            vector<int> path(0);
            int cur = i;
            v[i] = true;
            while(true) {
                path.push_back(cur);
                int next = c[cur];
                if(next == -1){
                    break;
                }
                if(v[next] == true){
                    break;
                }
                cur = next;
                v[cur] = true;
            }
            int status = -1;
            if(c[cur] == -1){
                status = cur < n? 1 : 2;
            }
            else {
                status = win[c[cur]];
                if(status == -1){
                    status = 0;
                }
            }
            for(int j = 0; j < path.size(); j++){
                win[path[j]] = status;
            }
        }
        vector<int> ans(3, 0);
        for(int i = 0; i < n; i++){
            ans[win[i]] ++;
        }
        cout << ans[1] << " " << ans[0] << " " << ans[2] << "\n";
    }
    
    return 0;
}
