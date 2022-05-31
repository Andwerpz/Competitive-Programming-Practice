#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1680A

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        if(a > d || c > b){
            cout << (a + c) << '\n';
        }
        else {
            cout << max(a, c) << '\n';
        }
    }
    
    return 0;
}
