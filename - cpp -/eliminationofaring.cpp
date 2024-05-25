#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1761B

//if there are exactly two unique values in the array, then you can only erase up to n / 2 + 1 elements. 
//otherwise, it's always possible to remove all elements. 
//don't ask me how i proved this; i guessed this during the contest. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        set<int> a;
        for(int i = 0; i < n; i++){
            int next;
            cin >> next;
            a.insert(next);
        }
        if(a.size() == 2){
            cout << n / 2 + 1 << "\n";
        }
        else {
            cout << n << "\n";
        }
    }
    
    return 0;
}