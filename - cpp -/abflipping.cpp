#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1896B

//find the first A and the last B, and we can always flip all the indices between them. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        string s;
        cin >> s;
        int a = 1e9;
        int b = -1;
        for(int i = 0; i < n; i++){
            if(s[i] == 'A'){
                a = min(a, i);
            }
            else {
                b = max(b, i);
            }
        }
        cout << max(b - a, 0) << "\n";
    }
    
    return 0;
}
