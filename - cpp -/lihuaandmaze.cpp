#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1797A

//you can just surround either the starting or ending points with walls. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n, m;
        cin >> n >> m;
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        int ansA = 4 - (x1 == 1) - (y1 == 1) - (x1 == n) - (y1 == m);
        int ansB = 4 - (x2 == 1) - (y2 == 1) - (x2 == n) - (y2 == m);
        cout << min(ansA, ansB) << "\n";
    }
    
    return 0;
}
