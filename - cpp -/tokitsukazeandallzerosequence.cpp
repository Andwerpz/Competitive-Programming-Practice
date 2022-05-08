#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1678A

//Just have to check for three cases: 

//if there are zeroes, then the ans is n - numZeroes

//if there are not zeroes, but there are two equal numbers, then the ans is n.

//else, the ans is n + 1

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        bool foundZero = false;
        int numZero = 0;
        bool foundSame = false;
        set<int> s;
        for(int i = 0; i < n; i++){
            int next;
            cin >> next;
            if(s.find(next) != s.end()){
                foundSame = true;
            }
            if(next == 0){
                numZero ++;
                foundZero = true;
            }
            s.insert(next);
        }
        if(foundZero){
            cout << (n - numZero) << endl;
        }
        else if(foundSame){
            cout << n << endl;
        }
        else{
            cout << (n + 1) << endl;
        }
    }
    
    return 0;
}
