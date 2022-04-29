#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1325A

//since gcd(x, 1) = 1, and lcm(x, 1) = x, we can always use the pair
//x - 1, 1.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int x;
        cin >> x;
        cout << "1 " << x - 1 << endl;
    }
    
    return 0;
}
