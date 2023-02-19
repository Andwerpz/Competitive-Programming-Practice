#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 05 D

//recursive backtracking to brute force all possible board positions. 

int solve(vector<vector<char>>& a, vector<vector<bool>>& v, vector<int>& b, int i) {
    //check for invalid placement
    bool isValid = true;
    int hitCnt = 0;
    int totalHits = 0;
    for(int i = 0; i < a.size(); i++){
        for(int j = 0; j < a.size(); j++){
            if(a[i][j] == 'O'){
                totalHits ++;
                if(v[i][j]){
                    hitCnt ++;
                }
            }
            if(v[i][j] && a[i][j] == 'X'){
                isValid = false;
            }
        }
    }
    if(!isValid) {
        return 0;
    }
    if(i == b.size()){
        return hitCnt == totalHits? 1 : 0;
    }
    int val = b[i];
    int ans = 0;
    for(int j = 0; j < a.size(); j++){
        for(int k = 0; k < a.size(); k++){
            //vertical
            if(j < a.size() - val + 1) {
                bool validPlacement = true;
                for(int l = 0; l < val; l++){
                    if(v[j + l][k]) {
                        validPlacement = false;
                        break;
                    }
                }
                if(validPlacement) {
                    for(int l = 0; l < val; l++){
                        v[j + l][k] = true;
                    }
                    ans += solve(a, v, b, i + 1);
                    for(int l = 0; l < val; l++){
                        v[j + l][k] = false;
                    }
                }
            }
            //horizontal
            if(k < a.size() - val + 1 && val != 1){
                bool validPlacement = true;
                for(int l = 0; l < val; l++){
                    if(v[j][k + l]) {
                        validPlacement = false;
                        break;
                    }
                }
                if(validPlacement) {
                    for(int l = 0; l < val; l++){
                        v[j][k + l] = true;
                    }
                    ans += solve(a, v, b, i + 1);
                    for(int l = 0; l < val; l++){
                        v[j][k + l] = false;
                    }
                }
            }
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    vector<vector<char>> a(n, vector<char>(n, 0));
    vector<vector<bool>> v(n, vector<bool>(n, false));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> a[i][j];
        }
    }
    vector<int> b(k);
    for(int i = 0; i < k; i++){
        cin >> b[i];
    }
    cout << solve(a, v, b, 0) << "\n";
    
    return 0;
}
