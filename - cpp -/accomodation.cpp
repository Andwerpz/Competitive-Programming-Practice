#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1804D

//greedy solution works, huh. 
//don't exactly know why. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    int amn = 0;
    int amx = 0;
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        int lcnt = 0;
        for(int j = 0; j < m; j++) {
            if(s[j] == '1'){
                lcnt ++;
            }
        }
        int mn = 0;
        int mx = 0;
        for(int j = 0; j < m - 1; j++){
            if(s[j] == '1' && s[j + 1] == '1') {
                j ++;
                mn ++;
            }
            if(mn == m / 4){
                break;
            }
        }
        for(int j = 0; j < m - 1; j++){
            if((s[j] == '0' && s[j + 1] == '0') || (s[j] == '0' && s[j + 1] == '1') || (s[j] == '1' && s[j + 1] == '0')) {
                j ++;
                mx ++;
            }
            if(mx == m / 4){
                break;
            }
        }
        mn = lcnt - mn;
        mx = lcnt - ((m / 4) - mx);
        //cout << mn << " " << mx << "\n";
        amn += mn;
        amx += mx;
    }
    cout << amn << " " << amx << "\n";
    
    return 0;
}
