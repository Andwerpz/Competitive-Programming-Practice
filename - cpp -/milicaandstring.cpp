#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1898A

//we can always make it so that there are k 'B' characters in one move or less. 
//it's pretty trivial. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        string s;
        cin >> s;
        int b_cnt = 0;
        for(int i = 0; i < n; i++){
            b_cnt += s[i] == 'B';
        }
        if(b_cnt == k){
            cout << "0\n";
            continue;
        }
        else if(b_cnt < k) {
            for(int i = 0; i < n; i++){
                b_cnt += s[i] == 'A';
                if(b_cnt == k){
                    cout << "1\n" << i + 1 << " B\n";
                    break;
                }
            }
        }
        else {
            for(int i = 0; i < n; i++){
                b_cnt -= s[i] == 'B';
                if(b_cnt == k){
                    cout << "1\n" << i + 1 << " A\n";
                    break;
                }
            }
        }
    }
    
    return 0;
}
