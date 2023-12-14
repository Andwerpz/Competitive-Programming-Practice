#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1901C

//floor dividing by 2 is just bitshifting the number to the right once. 
//then, the question is what is the minimum amount of bitshifts such that the bit representations are the same?

//note that the maximum amount of bitshifts is just equal to the power of the highest degree bit.
//we can just bitshift that many times, and everything equals 0. 

//then, in order to reduce the amount of shifts required, we must make all numbers have the highest
//degree bit, then once they all have it, we make them have the second highest degree bit and so on. 

//when solving this, I assumed that it was never optimal to ever add such that the highest degree bit changes. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    int tcnt = 0;
    while(t--){
        tcnt ++;
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        int add = 0;
        for(int i = 29; i >= 0; i--){
            bool has_bit = false;
            for(int j = 0; j < n; j++){
                if((a[j] >> i) & 1){
                    has_bit = true;
                }
            }
            if(!has_bit) {
                continue;
            }
            int min_add = 0;
            int max_add = (1 << i) - 1;
            for(int j = 0; j < n; j++){
                if((a[j] >> i) & 1) {
                    int tmp = a[j] - (1 << i);
                    max_add = min(max_add, (1 << i) - tmp - 1);
                }
                else {
                    min_add = max(min_add, (1 << i) - a[j]);
                }
            }
            if(min_add > max_add) {
                break;
            }
            add += min_add;
            for(int j = 0; j < n; j++){
                a[j] += min_add;
                a[j] ^= (1 << i);
            }
        }
        int ans = 0;
        for(int i = 0; i < n; i++){
            int cur = 0;
            int tmp = a[i];
            while(tmp != 0){
                cur ++;
                tmp /= 2;
            }
            ans = max(cur, ans);
        }
        cout << ans << "\n";
        if(ans <= n){
            for(int i = 0; i < ans; i++){
                cout << (i == 0? add : 0) << " ";
            }
            cout << "\n";
        }
    }
    
    return 0;
}
