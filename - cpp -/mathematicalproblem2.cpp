#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1986D

//one number has to be 2 digits, the rest are 1 digit. 

//just iterate through all possibilities of the 2 digit number, and create the resulting list of numbers. 

//if there exists a 0 in the list, then the answer is 0 as you can just multiply all the numbers together. 

//otherwise, it's best to add all the numbers. Note that the number 1 is an exception as multiplying it is better
//than adding it. 

//one final edge case is if there are only 1s, then the answer is 1. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        string s;
        cin >> s;
        if(n == 2) {
            cout << stoi(s) << "\n";
            continue;
        }
        int ans = 1e9;
        for(int i = 0; i < n - 1; i++){
            int cans = 0;
            vector<int> a(0);
            for(int j = 0; j < i; j++){
                a.push_back(s[j] - '0');
            }
            a.push_back((s[i] - '0') * 10 + (s[i + 1] - '0'));
            for(int j = i + 2; j < n; j++){
                a.push_back(s[j] - '0');
            }
            bool just_one = true;
            for(int i = 0; i < a.size(); i++){
                if(a[i] == 1){
                    continue;
                }
                just_one = false;
                if(a[i] == 0){
                    cans = 0;
                    break;
                }
                cans += a[i];
            }
            if(just_one) {
                cans = 1;
            }
            ans = min(ans, cans);
        }   
        cout << ans << "\n";
    }
    
    return 0;
}