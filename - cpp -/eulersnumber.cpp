#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//NCNA 2018 Regional E

//you can just brute force the calculation until the factorial becomes larger than 10^12. 
//then doing more steps won't change the answer relative to precision 10^-12. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    ld ans = 1;
    ld fac = 1;
    for(int i = 1; i <= n; i++){
        fac *= (ld) i;
        if(fac > 1e15) {
            break;
        }
        ans += 1.0 / fac;
    }
    cout << fixed << setprecision(15) << ans << "\n";
    
    return 0;
}
