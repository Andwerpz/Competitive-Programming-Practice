#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1877A

//the sum of efficiency among all the teams must be 0. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        int sum = 0;
        for(int i = 0; i < n - 1; i++){
            int a;
            cin >> a;
            sum += a;
        }
        cout << -sum << "\n";
    }
    
    return 0;
}
