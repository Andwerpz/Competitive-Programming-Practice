#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1919A

//since each player can choose to swap or not swap, it doesn't really matter who has which wallet. 
//then, since every move, the total value of the wallets goes down by 1, it's just parity. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int a, b;
        cin >> a >> b;
        cout << ((a + b) % 2 == 0? "Bob" : "Alice") << "\n";
    }
    
    return 0;
}
