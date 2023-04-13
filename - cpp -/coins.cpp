#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1814A

//if the target is even, then you can always make it, else, you need k to be odd, and less than or equal to the target to make it. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        ll n, k;
        cin >> n >> k;
        if(n % 2 == 0 || (k <= n && k % 2 == 1)){
            cout << "YES\n";
        }
        else {
            cout << "NO\n";
        }
    }
    
    return 0;
}
