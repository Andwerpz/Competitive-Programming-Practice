#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1699A

//notice that the answer to (a^b) + (b^c) + (c^a) must always be even. 

//thus if n is odd, then there is no way to make it. 

//in the case where n is even, there is a simple way to always make n:
//a = 0, b = 0, c = n / 2. 

//this works since 0 ^ c = c. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0) {
        int n;
        cin >> n;
        if(n % 2 == 1){
            cout << "-1\n";
            continue;
        }
        cout << "0 0 " << (n / 2) << "\n";
    }
    
    return 0;
}
