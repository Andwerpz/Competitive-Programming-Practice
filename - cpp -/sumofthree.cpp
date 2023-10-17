#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1886A

//we can solve it differently depending on the result of n % 3.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        int a, b, c;
        if(n % 3 == 0){
            a = 1;
            b = 4;
            c = 7;
        }
        else if(n % 3 == 1){
            a = 1;
            b = 2;
            c = 4;
        }
        else if(n % 3 == 2){
            a = 1;
            b = 2;
            c = 5;
        }
        if(n < a + b + c) {
            cout << "NO\n";
            continue;
        }
        n -= a + b + c;
        c += n;
        cout << "YES\n";
        cout << a << " " << b << " " << c << "\n";
    }
    
    return 0;
}
