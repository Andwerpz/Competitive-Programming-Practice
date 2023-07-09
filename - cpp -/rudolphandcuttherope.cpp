#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1846A

//if we have one rope, then the candy will hang at the height of the peg minus the length of the rope. 

//if we have multiple ropes, the candy will hang at the highest level out of all the pegs. 

//thus, we need to cut all ropes that make the candy hang above the ground. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        int ans = 0;
        while(n--){
            int a, b;
            cin >> a >> b;
            ans += a - b > 0;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
