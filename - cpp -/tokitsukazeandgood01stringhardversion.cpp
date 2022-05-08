#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1678B2

//my approach for the easy version was pretty dumb. 

//if you section the string into 2-character sequences, you'll see that there are 4 possible sequences:
//00, 11, 01, 10. You only need to change the 10 and 01 sequences to make the string valid. 

//so for the easy version, just count how many 10 and 01 sequences appear in the string. 

//to minimize the number of segments, just change the 10 and 01 sequences into the previous 11 or 00 sequence 
//encountered. 

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
        int ans = 0;
        int ans2 = 0;
        char prev = '.';
        for(int i = 0; i < s.size(); i += 2){
            if(s[i] != s[i + 1]){
                ans ++;
            }
            else{
                if(prev != s[i]){
                    ans2++;
                    prev = s[i];
                }
            }
        }
        cout << ans << " " << max(1, ans2) << endl;
    }
    
    return 0;
}
