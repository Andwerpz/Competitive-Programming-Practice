#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1842A

//lets say that the sum of all powers for tsondu is s(a), and the sum for tenzing is s(b). 

//when the monster a_i fights against b_j, they will both go down by min(a_i, b_j). It follows that s(a) and s(b)
//will also both go down by min(a_i, b_j). 

//since s(a) and s(b) go down at the same rate, regardless of what monster fights, the person with the greater sum will always win, 
//and if the sums are the same, they will tie. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        int n, m;
        cin >> n >> m;
        ll a = 0;
        ll b = 0;
        while(n--){
            ll next;
            cin >> next;
            a += next;
        }
        while(m--){
            ll next;
            cin >> next;
            b += next;
        }
        if(a == b){
            cout << "Draw\n";
        }
        else if(a > b) {
            cout << "Tsondu\n";
        }
        else {
            cout << "Tenzing\n";
        }
    }
    
    return 0;
}
