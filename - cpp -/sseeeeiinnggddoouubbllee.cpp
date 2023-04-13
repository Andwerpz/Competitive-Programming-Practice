#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1758A

//you can just reverse it and append. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        string s;
        cin >> s;
        cout << s; 
        reverse(s.begin(), s.end());
        cout << s << "\n";
    }
    
    return 0;
}
