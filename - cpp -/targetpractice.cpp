#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1873C

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int ans = 0;
        for(int i = 0; i < 10; i++){
            string s;
            cin >> s;
            for(int j = 0; j < 10; j++){
                if(s[j] == 'X') {
                    ans += min({(i + 1), (j + 1), (9 - i + 1), (9 - j + 1)});
                }
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
