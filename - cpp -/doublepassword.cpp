#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Kattis - doublepassword

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int ans = 1;
    string a, b;
    cin >> a >> b;
    for(int i = 0; i < 4; i++){
        if(a[i] != b[i]){
            ans *= 2;
        }
    }
    cout << ans << "\n";
    
    return 0;
}
