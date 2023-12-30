#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Rocky Mountain Regional 2016 A

//i love fizz buzz

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int x, y, n;
    cin >> x >> y >> n;
    for(int i = 1; i <= n; i++){
        bool div = false;
        if(i % x == 0){
            cout << "Fizz";
            div = true;
        }
        if(i % y == 0){
            cout << "Buzz";
            div = true;
        }
        if(!div) {
            cout << i;
        }
        cout << "\n";
    }
    
    return 0;
}
