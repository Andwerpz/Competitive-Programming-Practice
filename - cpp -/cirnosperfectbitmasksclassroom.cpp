#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1688A

//if x == 1, then the ans is 3. 

//else, if x is a power of two, then the ans is x + 1. 

//else, the ans is the lowest power of two in x's binary representation

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        bool isPowTwo = true;
        int x;
        cin >> x;
        if(x == 1){
            cout << "3\n";
            continue;
        }
        bool foundLow = false;
        int low = 1;
        while(x != 0){
            if(x % 2 == 1){
                if(!foundLow){
                    foundLow = true;
                }
                else {
                    isPowTwo = false;
                }
            }
            if(!foundLow){
                low *= 2;
            }
            x /= 2;
        }
        cout << (low + (isPowTwo? 1 : 0)) << "\n";
    }
    
    return 0;
}
