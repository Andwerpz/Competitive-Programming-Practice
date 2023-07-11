#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1844A

//if n = a + b, then whatever move the first person makes, the second one can just make the opposite move. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int a, b;
        cin >> a >> b;
        cout << (a + b) << "\n";
    }
    
    return 0;
}
