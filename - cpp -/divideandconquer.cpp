#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1762A

//if the sum is already even, then you don't need to do anything and the answer is 0. 

//if the sum is odd, then you need to somehow change the parity of 1 number. Since you can only do the floor
//div operation, just look at all the numbers, and figure out which number requires the fewest amount of
//operations to change it's parity. 

//note that at maximum, a number, a, can only sustain around log(a) operations before being equal to 0, so
//the complexity of this solution is O(n * log(a)). 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        int sum = 0;
        int minDiv = (int) 1e9;
        for(int i = 0; i < n; i++){
            int next;
            cin >> next;
            sum += next;
            if(next % 2 == 1){
                int div = 0;
                while(next % 2 == 1){
                    next /= 2;
                    div ++;
                }
                minDiv = min(div, minDiv);
            }
            else {
                int div = 0;
                while(next % 2 == 0){
                    next /= 2;
                    div ++;
                }
                minDiv = min(div, minDiv);
            }
        }
        cout << (sum % 2 == 0? 0 : minDiv) << "\n";
    }
    
    return 0;
}
