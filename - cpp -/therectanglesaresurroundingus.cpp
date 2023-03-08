#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 07 G

//brute force. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    while(n != 0){
        vector<vector<bool>> v(501, vector<bool>(501, false));
        for(int i = 0; i < n; i++){
            int a, b, c, d;
            cin >> a >> b >> c >> d;
            c--;
            d--;
            for(int r = a; r <= c; r++){
                for(int cl = b; cl <= d; cl++){
                    v[r][cl] = true;
                }
            }
        }
        int ans = 0;
        for(int i = 0; i < v.size(); i++){
            for(int j = 0; j < v.size(); j++){
                ans += v[i][j]? 1 : 0;
            }
        }
        cout << ans << "\n";
        cin >> n;
    }
    
    return 0;
}
