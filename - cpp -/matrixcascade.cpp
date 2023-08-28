#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1864D

//note that the top row can only be changed by doing operations on the top row, so any bit that is '1' on the
//top row needs to have an operation done to it. 

//In general, for each row, after we've done all the operations to the rows above it, we should update the contents
//of the row to reflect the operations, and if there are any '1's left on the row, we should register it as a new operation. 

//then, how do we actually do the operations? Note that doing the operations naively will result in a n^4 runtime, which is too slow. 
//instead, we can do them layer by layer. We can keep track of stuff going to the left, and going to the right, and stuff.... uhh. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<vector<bool>> a(n, vector<bool>(n, false));
        for(int i = 0; i < n; i++){
            string s;
            cin >> s;
            for(int j = 0; j < n; j++){
                a[i][j] = s[j] == '1';
            }
        }
        vector<bool> op(n, false);
        vector<bool> g_left(n, false);
        vector<bool> g_right(n, false);
        int ans = 0;
        for(int i = 0; i < n; i++){
            //update operation
            for(int j = 0; j < n; j++){
                op[j] = op[j] ^ g_left[j];
                op[j] = op[j] ^ g_right[j];
            }
            for(int j = 0; j < n - 1; j++){
                g_left[j] = g_left[j + 1];
            }
            g_left[n - 1] = false;
            for(int j = n - 1; j >= 1; j--){
                g_right[j] = g_right[j - 1];
            }
            g_right[0] = false;
            //apply the operation
            for(int j = 0; j < n; j++){
                a[i][j] = a[i][j] ^ op[j];
            }
            //check for new operations
            for(int j = 0; j < n; j++){
                if(a[i][j]){
                    ans ++;
                    op[j] = !op[j];
                    if(j != 0){
                        g_left[j - 1] = !g_left[j - 1];
                    }
                    if(j != n - 1){
                        g_right[j + 1] = !g_right[j + 1];
                    }
                }
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
