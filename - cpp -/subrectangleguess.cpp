#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1695A

//in order for micheal to guess correctly every time, there must be only 1 possible maximum
//value no matter the positioning of the subrectangle. 

//this value has to be the maximum value in the entire grid, since if it isn't, then we could
//always just place the rectangle over the maximum value in the grid to make the maximum rectangle value
//different.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n, m;
        cin >> n >> m;
        int max = -1e9 - 1;
        int ans = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                int next;
                cin >> next;
                if(next > max){
                    max = next;
                    int dr = std::max(i + 1, n - i);
                    int dc = std::max(j + 1, m - j);
                    ans = dr * dc;
                }
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
