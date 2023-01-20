#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Lab 01 F

//just simulate the problem statement

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0) {
        string s;
        cin >> s;
        int sq = 1;
        while(sq * sq < s.size()) {
            sq ++;
        }
        vector<vector<char>> a(sq, vector<char>(sq, 0));
        for(int i = 0; i < sq; i++){
            for(int j = 0; j < sq; j++){
                int ind = i * sq + j;
                if(ind >= s.size()) {
                    continue;
                }
                a[i][j] = s[ind];
            }
        }
        for(int i = 0; i < sq; i++){
            for(int j = 0; j < sq; j++){
                char c = a[sq - 1 - j][i];
                if(c == 0){
                    continue;
                }
                cout << c;
            }
        }
        cout << "\n";
    }
    
    return 0;
}
