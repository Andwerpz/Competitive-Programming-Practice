#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1774C

//bad problem D:
// - 12/19/2022 andrew

//actually not too bad, i just had to change 2 lines of code in my 2022 solution for it to work.

//all you have to notice is that the last group of same type of fights is what matters. 

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
                ans = i + 1;
            }
            cout << ans << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
