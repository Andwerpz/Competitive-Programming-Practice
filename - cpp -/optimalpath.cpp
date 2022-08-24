#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1700A

//the optimal path is to first go straight left m tiles, then go down n tiles. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        ll n, m;
        cin >> n >> m;
        cout << ((m - 1) * m) / 2 + ((n * (n + 1)) / 2) * m << "\n";
    }
    
    return 0;
}
