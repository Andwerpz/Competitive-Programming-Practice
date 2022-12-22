#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1767A

//you just have to make sure that the triangle isn't aligned with both the x and y axis. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int x1, y1, x2, y2, x3, y3;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        if((x1 == x2 || x2 == x3 || x3 == x1) && (y1 == y2 || y2 == y3 || y3 == y1)) {
            cout << "NO\n";
        }
        else {
            cout << "YES\n";
        }
    }
    
    return 0;
}
