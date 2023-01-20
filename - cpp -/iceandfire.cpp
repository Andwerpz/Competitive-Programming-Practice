#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1774C

//bad problem D:

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        string s;
        cin >> s;
        int ans = 1;
        char prev = s[0];
        cout << ans << " ";
        for(int i = 1; i < n - 1; i++){
            if(s[i] != prev) {
                prev = s[i];
                ans = i + 2;
            }
            ans --;
            ans = max(ans, 1);
            cout << ans << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
