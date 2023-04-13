#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1421B

//notice that all you have to do to prevent S to reach F is to modify what S can reach directly. 
//if both of the values adjacent to S are different from both of the values adjacent to F, then it is guaranteed
//that S cannot reach F. 

//from there, it's just casework. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<string> g(n);
        for(int i = 0; i < n; i++){
            cin >> g[i];
        }
        char a = g[0][1];
        char b = g[1][0];
        char c = g[n - 1][n - 2];
        char d = g[n - 2][n - 1];
        if(a == b && b != c && c == d){
            cout << "0\n";
            continue;
        }
        if(a == b && b == c && c == d){
            cout << "2\n";
            cout << "1 2\n";
            cout << "2 1\n";
            continue;
        }
        if(a != b && c == d){
            cout << "1\n";
            if(b == c){
                cout << "2 1\n";
            }
            else {
                cout << "1 2\n";
            }
            continue;
        }
        if(a == b && c != d){
            cout << "1\n";
            if(c == a){
                cout << n << " " << n - 1 << "\n";
            }
            else {
                cout << n - 1 << " " << n << "\n";
            }
            continue;
        }
        if(a != b && c != d){
            cout << "2\n";
            if(a == c) {
                cout << "1 2\n";
                cout << n - 1 << " " << n << "\n";
            }
            else {
                cout << "2 1\n";
                cout << n - 1 << " " << n << "\n";
            }
            continue;
        }
    }
    
    return 0;
}
