#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1862A

//implementation. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        vector<string> a(n, "");
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        string name = "vika";
        int ptr = 0;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(a[j][i] == name[ptr]) {
                    ptr ++;
                    break;
                }
            }
            if(ptr == name.size()){
                break;
            }
        }
        cout << (ptr == name.size()? "YES\n" : "NO\n");
    }
    
    return 0;
}
