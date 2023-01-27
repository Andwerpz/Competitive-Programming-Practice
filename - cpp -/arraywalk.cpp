#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//ACPC Weekly Problem Set #1 (Spring 2023) G

//you don't even have to use dp to solve this. Actually, idk how you would use dp...

//notice that each move to the left allows you to 'collect' the values of any pair of numbers again. 
//it becomes pretty obvious that spending left moves in different indexes is non-optimal. 

//with this, a greedy solution becomes apparent; for each pair of numbers, figure out how many times we can re-collect
//their values. Then the answer is simply the maximum out of any of the n - 1 pairs. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n, k, z;
        cin >> n >> k >> z;
        vector<ll> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        ll ans = 0;
        vector<ll> pfx(n, 0);
        pfx[0] = a[0];
        for(int i = 1; i < n; i++){
            pfx[i] = a[i] + pfx[i - 1];
        }
        for(int i = 0; i < n - 1; i++){
            ll moves = k;
            //to get to where you want
            ll sum = pfx[i];
            moves -= i;
            if(moves < 0){
                continue;
            }
            ll numRepeats = min(moves / 2, (ll)z);
            sum += (a[i] + a[i + 1]) * numRepeats;
            moves -= numRepeats * 2;
            int r = i + moves;
            sum += pfx[r] - pfx[i];
            ans = max(ans, sum);
            //cout << i << " : " << numRepeats << " " << a[i] << "\n";
        }
        cout << ans << "\n";
    }
    
    return 0;
}
