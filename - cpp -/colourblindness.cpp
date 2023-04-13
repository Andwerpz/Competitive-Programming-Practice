#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1722B

//implementation. Just turn all of the greens into blue, and vice versa. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        string a, b;
        cin >> a >> b;
        for(int i = 0; i < a.size(); i++){
            if(a[i] == 'G'){
                a[i] = 'B';
            }
            if(b[i] == 'G'){
                b[i] = 'B';
            }
        }
        cout << (a == b? "YES\n" : "NO\n");
    }
    
    return 0;
}
