#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2011 C

//the rules on the input practically give away how you are supposed to solve this problem:
//"The hieroglyphs may be distorted but each has a shape that is topologically equivalent to one of the symbols."

//this essentially means that the number of 'holes' in each shape will match up with one of the given symbols. 
//at this point, it's sufficient to just find all connected components of white and black regions, and
//classify the black regions based on how many isolated connected white regions they touch. 

int hex_to_int(char a) {
    if('0' <= a && a <= '9') {
        return a - '0';
    }
    return (a - 'a') + 10;
}

void solve(int h, int w, int case_no) {
    vector<vector<bool>> is_black(h, vector<bool>(w * 4, false));
    for(int i = 0; i < h; i++){
        string line;
        cin >> line;
        for(int j = 0; j < w; j++){
            int bits = hex_to_int(line[j]);
            for(int k = 0; k < 4; k++){
                if(bits & (1 << (3 - k))) {
                    is_black[i][j * 4 + k] = true;
                }
            }
        }
    }
    // cout << "PRINT ARRAY : " << endl;
    // for(int i = 0; i < is_black.size(); i++){
    //     for(int j = 0; j < is_black[i].size(); j++){
    //         cout << is_black[i][j] << " ";
    //     }
    //     cout << "\n";
    // }
    vector<vector<int>> conn(h, vector<int>(w * 4, -1));
    vector<vector<bool>> v(h, vector<bool>(w * 4, false));
    vector<bool> t_edge(0);
    vector<bool> conn_black(0);
    vector<set<int>> touching(0);
    vector<int> dr = {-1, 1, 0, 0};
    vector<int> dc = {0, 0, -1, 1};
    int n_connID = 0;
    for(int i = 0; i < is_black.size(); i++){
        for(int j = 0; j < is_black[i].size(); j++){
            if(v[i][j]){
                continue;
            }
            bool touchingEdge = false;
            stack<pair<int, int>> s;
            v[i][j] = true;
            s.push({i, j});
            touching.push_back(set<int>());
            while(s.size() != 0){
                int r = s.top().first;
                int c = s.top().second;
                s.pop();
                conn[r][c] = n_connID;
                for(int k = 0; k < 4; k++){
                    int nr = r + dr[k];
                    int nc = c + dc[k];
                    if(nr < 0 || nc < 0 || nr >= is_black.size() || nc >= is_black[0].size()) {
                        touchingEdge = true;
                        continue;
                    }
                    if(is_black[i][j] != is_black[nr][nc]) {
                        if(v[nr][nc]) {
                            touching[n_connID].insert(conn[nr][nc]);
                            touching[conn[nr][nc]].insert(n_connID);
                        }
                        continue;
                    }
                    if(v[nr][nc]) {
                        continue;
                    }
                    v[nr][nc] = true;
                    s.push({nr, nc});
                }
            }
            n_connID ++;
            conn_black.push_back(is_black[i][j]);
            t_edge.push_back(touchingEdge);
        }
    }
    // cout << "PRINT COON : " << endl;
    // for(int i = 0; i < is_black.size(); i++){
    //     for(int j = 0; j < is_black[i].size(); j++){
    //         cout << conn[i][j] << " ";
    //     }
    //     cout << "\n";
    // }
    vector<char> ans(0);
    for(int i = 0; i < conn_black.size(); i++){
        if(!conn_black[i]) {
            continue;
        }
        int nr_holes = 0;
        for(auto j = touching[i].begin(); j != touching[i].end(); j++){
            int n_conn = *j;
            if(t_edge[n_conn]) {
                continue;
            }
            if(conn_black[n_conn]) {
                continue;
            }
            nr_holes ++;
        }
        if(nr_holes == 1){
            ans.push_back('A');
        }
        else if(nr_holes == 3) {
            ans.push_back('J');
        }
        else if(nr_holes == 5) {
            ans.push_back('D');
        }
        else if(nr_holes == 4) {
            ans.push_back('S');
        }
        else if(nr_holes == 0) {
            ans.push_back('W');
        }
        else if(nr_holes == 2) {
            ans.push_back('K');
        }
    }
    sort(ans.begin(), ans.end());
    cout << "Case " << case_no << ": ";
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i];
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int h, w;
    int case_no = 0;
    cin >> h >> w;
    while(h != 0 || w != 0) {
        case_no ++;
        solve(h, w, case_no);
        cin >> h >> w;
    }
    
    return 0;
}
