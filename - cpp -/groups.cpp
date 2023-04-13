#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1598B

//you can try all combinations of days. 

//students can be available both days, only one day, or none of the days. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<vector<int>> a(n, vector<int>(5));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < 5; j++){
                cin >> a[i][j];
            }
        }
        bool isValid = false;
        for(int i = 0; i < 5; i++){
            for(int j = i + 1; j < 5; j++){
                int u = 0;
                int v = 0;
                int b = 0;
                int none = 0;
                for(int k = 0; k < n; k++){
                    if(a[k][i] == 0 && a[k][j] == 0){
                        none ++;
                    }
                    else if(a[k][i] == 1 && a[k][j] == 1){
                        b ++;
                    }
                    else if(a[k][i] == 1){
                        u ++;
                    }
                    else {
                        v ++;
                    }
                }
                if(none != 0){
                    continue;
                }
                if(u > n / 2 || v > n / 2){
                    continue;
                }
                isValid = true;
            }
        }
        cout << (isValid? "YES\n" : "NO\n");
    }
    
    return 0;
}
