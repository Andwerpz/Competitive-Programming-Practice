#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1916A

//if the product of the numbers given divides 2023 evenly, then the remaining sequence can just be
//the quotient and a bunch of 1s. 

//otherwise, it's impossible. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        int b = 1;
        for(int i = 0; i < n; i++){
            int next;
            cin >> next;
            b *= next;
            if(b > 2023) {
                b = 2024;
            }
        }
        if(b > 2023 || 2023 % b != 0) {
            cout << "NO\n";
            continue;
        }
        int d = 2023 / b;
        cout << "YES\n";
        cout << d << " ";
        for(int i = 1; i < k; i++){
            cout << "1 ";
        }
        cout << "\n";
    }
    
    return 0;
}
