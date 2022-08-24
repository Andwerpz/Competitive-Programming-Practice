#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1680C

//the cost is the maximum between zeroes remaining in the string, and ones removed from the string. 
//it is always optimal to try to equalize the two values, since if you try to minimize one, then the other will 
//always go up. 

//to check if a certain cost k is achievable, we can use a 2ptr algorithm. 

//thus, binary search across all costs k

bool isValid(string& s, int val, int oneAmt, int zeroAmt){
    int r = 0;
    int zeroCnt = 0;
    int oneCnt = 0;
    for(int i = 0; i < s.size(); i++){
        while(r != s.size() && (zeroCnt + (s[r] == '0'? 1 : 0) <= val || r == i)){
            zeroCnt += (s[r] == '0'? 1 : 0);
            oneCnt += (s[r] == '1'? 1 : 0);
            r ++;
        }
        if(zeroCnt <= val && oneAmt - oneCnt <= val){
            return true;
        }
        zeroCnt -= (s[i] == '0'? 1 : 0);
        oneCnt -= (s[i] == '1'? 1 : 0);
    }
    if(zeroCnt <= val && oneAmt - oneCnt <= val){
        return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        string s;
        cin >> s;
        int oneAmt = 0;
        int zeroAmt = 0;
        for(char c : s){
            if(c == '0'){
                zeroAmt ++;
            }
            else{
                oneAmt ++;
            }
        }
        int low = 0;
        int high = s.size();
        int mid = low + (high - low) / 2;
        int ans = s.size();
        while(low <= high){
            if(isValid(s, mid, oneAmt, zeroAmt)){
                high = mid - 1;
                ans = min(ans, mid);
            }
            else{
                low = mid + 1;
            }
            mid = low + (high - low) / 2;
        }
        cout << ans << endl;
    }
    
    return 0;
}
