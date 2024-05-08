#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//ACPC 2024 Spring Contest - C

//we can just assign problems cyclically: "AB", "CD", "EA", "BC", "DE"
//the maximum number of problems we can assign to each person is floor(n / 2).

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    int ans = n / 2;
    if(n == 1){
        ans = 1;
    }
    cout << ans << "\n";
    int ptr = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < ans; j++){
            cout << (char) (ptr + 'A');
            ptr = (ptr + 1) % n;
        }
        cout << "\n";
    }
    
    return 0;
}
