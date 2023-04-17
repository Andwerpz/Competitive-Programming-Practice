#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 10 E

//i used meet in the middle, but brute force backtracking works as well, because the knight has limited movement options 
//everywhere except the middle. 

vector<int> dr = {-2, -2, -1, -1, 1, 1, 2, 2};
vector<int> dc = {-1, 1, -2, 2, -2, 2, -1, 1};

void solve(vector<vector<char>>& g, set<vector<vector<char>>>& s, int cnt) {
    if(cnt == 0){
        vector<vector<char>> c(5, vector<char>(5));
        for(int i = 0; i < 5; i++){
            for(int j = 0; j < 5; j++){
                c[i][j] = g[i][j];
            }
        }
        s.insert(c);
        return;
    }
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(g[i][j] != ' ') {
                continue;
            }
            for(int k = 0; k < dr.size(); k++){
                int nr = i + dr[k];
                int nc = j + dc[k];
                if(nr < 0 || nc < 0 || nr >= 5 || nc >= 5){
                    continue;
                }
                char tmp = g[nr][nc];
                g[nr][nc] = g[i][j];
                g[i][j] = tmp;
                solve(g, s, cnt - 1);
                tmp = g[nr][nc];
                g[nr][nc] = g[i][j];
                g[i][j] = tmp;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    string tmp;
    getline(cin, tmp);
    while(t-- > 0){
        vector<vector<char>> dest(5, vector<char>(5));
        for(int i = 0; i < 5; i++){
            string line;
            getline(cin, line);
            for(int j = 0; j < 5; j++){
                dest[i][j] = line[j];
            }
        }
        vector<vector<char>> g = {
            {'1', '1', '1', '1', '1'},
            {'0', '1', '1', '1', '1'},
            {'0', '0', ' ', '1', '1'},
            {'0', '0', '0', '0', '1'},
            {'0', '0', '0', '0', '0'},
        };
        int ans = -1;
        for(int i = 0; i <= 10; i++){
            set<vector<vector<char>>> a;
            set<vector<vector<char>>> b;
            solve(dest, a, i / 2);
            solve(g, b, i / 2 + (i % 2));
            for(auto j = a.begin(); j != a.end(); j++){
                if(b.find(*j) != b.end()) {
                    ans = i;
                    break;
                }
            }
            if(ans != -1){
                break;
            }
        }
        if(ans == -1){
            cout << "Unsolvable in less than 11 move(s).\n";
        }
        else {
            cout << "Solvable in " << ans << " move(s).\n";
        }
    }
    
    return 0;
}
