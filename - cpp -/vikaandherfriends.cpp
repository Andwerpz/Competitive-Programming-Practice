#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1848A

//since the graph made by the grid is bipartite, we just need to check if one friend is on the same
//color as vika. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m, k;
        cin >> n >> m >> k;
        int x, y;
        cin >> x >> y;
        int v = (x + y) % 2;
        bool found = false;
        for(int i = 0; i < k; i++){
            cin >> x >> y;
            if((x + y) % 2 == v){
                found = true;
            }
        }
        cout << (!found? "YES\n" : "NO\n");
    }
    
    return 0;
}
