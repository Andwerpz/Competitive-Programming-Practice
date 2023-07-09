#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1846B

//just do normal tic tac toe win checking. 

bool solve(vector<string>& a, char c) {
    for(int i = 0; i < 3; i++){
        if(a[i][0] == a[i][1] && a[i][1] == a[i][2] && a[i][2] == c){
            return true;
        }
        if(a[0][i] == a[1][i] && a[1][i] == a[2][i] && a[2][i] == c){
            return true;
        }
    }
    if(a[0][0] == a[1][1] && a[1][1] == a[2][2] && a[2][2] == c){
        return true;
    }
    if(a[0][2] == a[1][1] && a[1][1] == a[2][0] && a[2][0] == c){
        return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    string s = "XO+";
    while(t--){
        vector<string> a(3);
        for(int i = 0; i < 3; i++){
            cin >> a[i];
        }
        string ans = "DRAW";
        for(int i = 0; i < 3; i++){
            if(solve(a, s[i])) {
                ans = s[i];
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
