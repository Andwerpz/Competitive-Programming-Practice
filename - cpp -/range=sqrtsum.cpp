#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1758D

//for n = 1, and n = 2, we can do custom solutions. 

//for n >= 3, lets make our target sum to be (n + 1)^2. This means that the range is n + 1. 
//lets start with an array a, and slowly change it to become the final answer. Initially, a = {1, 2, 3 ... n - 1, n + 2}. 

//notice that by changing the numbers in the middle between 1 and n + 1, we can add a maximum of (n - 2) * 3 to the sum. 
//also note that without affecting the range, we can add 1 to all numbers in a, and increment the sum by n.
//these two properties combined makes us able to make sum(a) equal to all values above the initial sum(a), which is equal to
//n + 2 + n * (n - 1) / 2, which is less than (n + 1)^2.  

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        ll n;
        cin >> n;
        if(n == 1) {
            cout << "1\n";
            continue;
        }
        else if(n == 2){
            cout << "1 3\n";
            continue;
        }
        ll target = (n + 1) * (n + 1);
        ll max = n + 2;
        ll sum = max + n * (n - 1) / 2;
        //cout << sum << "\n";
        ll diff = target - sum;
        ll base = diff / n;
        diff %= n;
        //cout << diff << "\n";
        cout << 1 + base << " ";
        for(int i = max - 3; i >= 2; i--){
            ll add = min(diff, 2ll);
            diff -= add;
            cout << i + add + base << " ";
        }
        cout << max + base << "\n";
    }
    
    return 0;
}
