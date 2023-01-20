#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1762B

//since we can at most double each number, if we make each number a power of 2, then if we take a pair of numbers
//the smaller number should be able to divide the bigger one since they are both powers of 2. 

//we can make each number into a power of 2 since the next power of 2 for a positive integer is always within double of
//it's own value. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        cout << n << "\n";
        for(int i = 0; i < n; i++){
            int pow = 1;
            while(pow < a[i]) {
                pow *= 2;
            }
            cout << (i + 1) << " " << (pow - a[i]) << "\n";
        }
    }
    
    return 0;
}
