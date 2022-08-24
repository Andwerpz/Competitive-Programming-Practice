#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1680B

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n, m;
        cin >> n >> m;
        vector<string> c(n);
        for(int i = 0; i < n; i++){
            cin >> c[i];
        }
        int minX = -1;
        bool isValid = true;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(c[i][j] == 'R'){
                    if(minX == -1){
                        minX = j;
                    }
                    else if(j < minX){
                        isValid = false;
                    }
                }
            }
        }
        cout << (isValid? "YES\n" : "NO\n");
    }
    
    return 0;
}
