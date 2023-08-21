#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1850C

//implementation. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        string ans = "";
        for(int i = 0; i < 8; i++){
            string a;
            cin >> a;
            for(int j = 0; j < 8; j++){
                if(a[j] != '.'){
                    ans += a[j];
                }
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
