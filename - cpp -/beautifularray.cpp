#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//ACPC Week 6D

//split the contents of s into the part that contributes to the beauty, which is exactly b * k, 
//and the part that doesn't contribute, s - b * k. 

//First, if s < b * k, then you don't have enough sum to create the desired array. 
//Second, if (s - b * k) / n >= k, then any array created with sum s must have beauty greater than b. 

//else, you can always create the desired array. From here, it's just implementation. 
//you can first set one value to b * k, and add to the rest at most k - 1 until the sum equals s. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        ll n, k, b, s;
        cin >> n >> k >> b >> s;
        ll extra = s - b * k;
        if(extra > (k - 1) * n || b * k > s) {
            cout << "-1\n";
            continue;
        }
        for(int i = 0; i < n; i++){
            ll next = 0;
            if(i == 0){
                next += b * k;
            }
            ll add = min(k - 1, extra);
            extra -= add;
            next += add;
            cout << next << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
