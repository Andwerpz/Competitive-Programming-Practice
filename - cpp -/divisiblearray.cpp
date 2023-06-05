#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1828A

//the minimum value for a[i] is i. The total sum of a of length n where each element is the minimum is equal to 
//n * (n + 1) / 2. 

//Since we want the sum of a to be divisible by n, we want (n * (n + 1) / 2) % n === 0. Since the first element of a just
//has to be divisible by 1, we can add the remainder of n and (n * (n + 1) / 2) to it. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        int sum = (n * (n + 1)) / 2;
        int rem = sum % n;
        cout << 1 + rem << " \n"[1 == n];
        for(int i = 2; i <= n; i++){
            cout << i << " \n"[i == n];
        }
    }
    
    return 0;
}
