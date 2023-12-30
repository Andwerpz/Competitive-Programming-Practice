#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ACPC 2023 Fall Contest G

//we can brute force to find every character independently, then print the answer when we're done. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string ans(20, 'a');
    for(int i = 0; i < 20; i++){
        int low_wrong = 1e9;
        char c = 'a';
        string guess(20, 'a');
        for(int j = 0; j < 26; j++){
            guess[i] = 'a' + j;
            cout << guess << endl;
            int wrong;
            cin >> wrong;
            if(wrong < low_wrong) {
                low_wrong = wrong;
                c = 'a' + j;
            }
        }
        ans[i] = c;
    }
    cout << ans << "\n";
    
    return 0;
}
