#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        for(int i = 1; i <= n; i++){
            for(int j = 0; j < i; j++){
                cout << (j == 0 || j == i - 1? 1 : 0) << " \n"[j == i - 1];
            }
        }
    }
    
    return 0;
}
