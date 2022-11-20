#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//A&M Fall 2022 F

//implementation

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    if(m % 2 == 0){
        cout << "NO\n";
        return 0;
    }
    bool isValid = true;
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        for(int j = 0; j < m; j++){
            if(j == m / 2) {
                if(s[j] != '#'){
                    isValid = false;
                }
            }
            else {
                if(s[j] != '^'){
                    isValid = false;
                }
            }
        }
    }
    cout << (isValid? "YES\n" : "NO\n");
    
    return 0;
}
