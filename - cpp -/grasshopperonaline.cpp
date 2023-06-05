#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1837A

//if x is not divisible by k, then we can just jump directly to the goal. 

//if x is divisible by k, then x - 1 can't be divisible by k, since k >= 2. 
//thus, we can jump to x - 1, then jump to x. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int x, k;
        cin >> x >> k;
        if(x % k == 0){
            cout << "2\n" << (x - 1) << " " << 1 << "\n";
        }
        else {
            cout << "1\n" << x << "\n";
        }
    }
    
    return 0;
}
