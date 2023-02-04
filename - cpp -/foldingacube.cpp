#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//RMRC 2019 Practice C

//just imagine starting a cube on one of the marked tiles.
//roll it around and see which bottom faces land on which tiles. 

//if two different tiles have the same bottom face land on it, then you know that the configuratin is invalid. 

string up(string a) {
    char tmp = a[0];
    a[0] = a[1];
    a[1] = a[5];
    a[5] = a[3];
    a[3] = tmp; 
    return a;
}

string down(string a) {
    char tmp = a[0];
    a[0] = a[3];
    a[3] = a[5];
    a[5] = a[1];
    a[1] = tmp;
    return a;
}

string left(string a) {
    char tmp = a[0];
    a[0] = a[4];
    a[4] = a[5];
    a[5] = a[2];
    a[2] = tmp;
    return a;
}

string right(string a) {
    char tmp = a[0];
    a[0] = a[2];
    a[2] = a[5];
    a[5] = a[4];
    a[4] = tmp;
    return a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<string> a(6, "");
    int sr, sc;
    for(int i = 0; i < 6; i++) {
        cin >> a[i];
    }
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 6; j++){
            if(a[i][j] == '#') {
                sr = i;
                sc = j;
            }
        }
    }
    set<char> s;
    vector<vector<string>> v(6, vector<string>(6, ""));
    queue<pair<int, int>> q;
    q.push({sr, sc});
    v[sr][sc] = "GNESWU";
    vector<int> dr = {-1, 1, 0, 0};
    vector<int> dc = {0, 0, -1, 1};
    bool isValid = true;
    while(q.size() != 0) {
        int r = q.front().first;
        int c = q.front().second;
        q.pop();
        string state = v[r][c];
        if(s.find(state[0]) != s.end()) {
            isValid = false;
        }
        s.insert(state[0]);
        for(int i = 0; i < 4; i++){
            int nr = r + dr[i];
            int nc = c + dc[i];
            if(nr < 0 || nc < 0 || nr >= 6 || nc >= 6) {
                continue;
            }
            if(a[nr][nc] == '.' || v[nr][nc] != "") {
                continue;
            }
            string nState = "";
            if(i == 0) {
                nState = up(state);
            }
            else if(i == 1){
                nState = down(state);
            }
            else if(i == 2){
                nState = left(state);
            }
            else if(i == 3){
                nState = right(state);
            }
            v[nr][nc] = nState;
            q.push({nr, nc});
        }
    }
    cout << (isValid? "can fold\n" : "cannot fold\n");
    
    return 0;
}
