#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1766A

//since numbers can't have leading zeroes, only numbers of the form a * 10^b can be considered extremely round. 

//we just need to count how many digits the number has, excluding the most significant digit, and multiply it by 9. 
//then add the value in the most significant digit, and that's the answer. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0) {
        int n;
        cin >> n;
        int ans = 0;
        while(n >= 10) {
            ans += 9;
            n /= 10;
        }
        ans += n;
        cout << ans << "\n";
    }
    
    return 0;
}
