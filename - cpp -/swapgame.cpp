#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1747C

//bob can force alice to have 1 number on her turn, which is a[0].
//alice can force bob to have only one of any number a[1] - a[n - 1] on his turn.

//if a[0] <= min(a[1] - a[n - 1]), then bob wins, else alice wins. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        int bob = a[0];
        int alice = a[1];
        for(int i = 1; i < n; i++){
            alice = min(alice, a[i]);
        }
        cout << (bob <= alice? "BOB\n" : "ALICE\n");
    }
    
    return 0;
}
