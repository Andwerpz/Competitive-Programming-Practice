#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Lab 02 A

//implementation sucks D:

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<vector<int>> a(4, vector<int>(4, 0));
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            cin >> a[i][j];
        }
    }
    vector<vector<int>> ans(4, vector<int>(4, 0));
    int dr = 0;
    int dc = 0;
    int t;
    cin >> t;
    if(t == 0){
        dc = 1;
    }
    if(t == 1) {
        dr = 1;
    }
    if(t == 2){
        dc = -1;
    }
    if(t == 3){
        dr = -1;
    }
    if(dr == 0){
        for(int i = 0; i < 4; i++){
            int pval = -1;
            int p = dc == 1? 0 : 3;
            for(int j = dc == 1? 0 : 3; j != 4 && j != -1; j += dc) {
                if(a[i][j] == 0){
                    continue;
                }
                if(pval == a[i][j]) {
                    ans[i][p] = pval * 2;
                    pval = -1;
                    p += dc;
                }
                else {
                    if(pval != -1){
                        ans[i][p] = pval;
                        p += dc;
                    }
                    pval = a[i][j];
                }
            }
            if(pval != -1) {
                ans[i][p] = pval;
            }
        }
    }
    else {
        for(int i = 0; i < 4; i++){
            int pval = -1;
            int p = dr == 1? 0 : 3;
            for(int j = dr == 1? 0 : 3; j != 4 && j != -1; j += dr) {
                if(a[j][i] == 0){
                    continue;
                }
                if(pval == a[j][i]) {
                    ans[p][i] = pval * 2;
                    pval = -1;
                    p += dr;
                }
                else {
                    if(pval != -1){
                        ans[p][i] = pval;
                        p += dr;
                    }
                    pval = a[j][i];
                }
            }
            if(pval != -1){
                ans[p][i] = pval;
            }
        }
    }
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            cout << ans[i][j] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
