#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//ACPC Weekly Problemset 3G

//for the ith number, consider how many different sfx subarrays it will be in: i + 1. 
//then, take the jth number, j > i, and count how many prefix subarrays it is in: n - j.
//if you multiply those two numbers together, then the result is equal to the amount of subarrays they are both in. 

//iterate through the array. 
//for each unique number, we can just keep track of a running sum of the first value; i + 1, 
//update the answer by multiplying the running sum for that number by n - i.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        map<int, ll> m;
        ll ans = 0;
        for(int i = 0; i < n; i++){
            int a;
            cin >> a;
            if(m.find(a) == m.end()){
                m.insert({a, 0});
            }
            ans += (ll) (m.find(a) -> second) * (ll) (n - i);
            m.find(a) -> second += i + 1;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
