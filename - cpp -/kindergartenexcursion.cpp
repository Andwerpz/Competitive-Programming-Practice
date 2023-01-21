#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 01 B

//i don't know how to prove that this is correct, it just works 

//basically, you want to move lower numbers to the left. So for each number, the amount of required swaps involving this number is
//equal to the number of values to it's left that are greater than it. The sum is the total number of swaps. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll ans = 0;
    string s;
    cin >> s;
    ll cnt0 = 0;
    ll cnt1 = 0;
    ll cnt2 = 0;
    for(int i = 0; i < s.size(); i++){
        if(s[i] == '0') {
            cnt0 ++;
            ans += cnt1 + cnt2;
        }
        if(s[i] == '1') {
            cnt1 ++;
            ans += cnt2;
        }
        if(s[i] == '2') {
            cnt2 ++;
        }
    }
    cout << ans << "\n";
    
    return 0;
}
