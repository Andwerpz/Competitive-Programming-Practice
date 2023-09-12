#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1867B

//first, we can compute the minimum amount of bits required to make s into a palindrome; R. 
//note that n - R will also denote the upper bound of bits that can be used to make s into a palindrome. 

//next, in the interval [R, n - R], can all of these bit amounts be used to convert s into a palindrome?
//note that if n is odd, then yes, all of them can be used. This is because the center bit in s can be
//toggled on and off if you have an extra bit. 

//but if n is even, then the answer is no; only every other bit can be used. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        string s;
        cin >> s;
        int req = 0;
        for(int i = 0; i < n / 2; i++){
            if(s[i] != s[n - 1 - i]) {
                req ++;
            }
        }
        vector<bool> ans(n + 1);
        for(int i = 0; i < ans.size(); i++){
            if(min(i, n - i) >= req) {
                ans[i] = true;
            }
        }
        if(n % 2 == 0){
            for(int i = 0; i < ans.size(); i++){
                if(!ans[i]) {
                    continue;
                }
                if((req + i) % 2 == 1){
                    ans[i] = false;
                }
            }
        }
        for(int i = 0; i < ans.size(); i++){
            cout << ans[i];
        }
        cout << "\n";
    }
    
    return 0;
}
