#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 06 A

//implementation

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int r, c;
    cin >> r >> c;
    vector<vector<bool>> v(r, vector<bool>(c, false));
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        int a, b;
        cin >> a >> b;
        a --;
        b --;
        v[a][b] = true;
    }
    vector<int> dr = {-1, -1, -1, 0, 0, 1, 1, 1};
    vector<int> dc = {-1, 0, 1, -1, 1, -1, 0, 1};
    vector<int> ans(9, 0);
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            if(!v[i][j]){
                continue;
            }
            int cnt = 0;
            for(int k = 0; k < dr.size(); k++){
                int nr = i + dr[k];
                int nc = j + dc[k];
                if(nr < 0 || nc < 0 || nr >= r || nc >= c){
                    continue;
                }
                if(v[nr][nc]){
                    cnt ++;
                }
            }
            ans[cnt] ++;
        }
    }
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i] << " ";
    }
    cout << "\n";
    
    return 0;
}
