#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1837B

//the answer is the maximum amount of consective '>' or '<' that are the same. 

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
        char prev = ' ';
        int ans = 0;
        int cnt = 0;
        for(int i = 0; i < n; i++){
            if(prev != s[i]) {
                cnt = 0;
                prev = s[i];
            }
            cnt ++;
            ans = max(ans, cnt);
        }
        ans += 1;
        cout << ans << "\n";
    }
    
    return 0;
}
