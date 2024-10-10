#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//Kattis - woodcutting

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<ld> a(n);
        for(int i = 0; i < n; i++){
            int amt;
            cin >> amt;
            ld sum = 0;
            for(int j = 0; j < amt; j++){
                ld next;
                cin >> next;
                sum += next;
            }
            a[i] = sum;
        }
        sort(a.begin(), a.end());
        ld sum = 0;
        ld avg = 0;
        for(int i = 0; i < n; i++){
            sum += a[i];
            avg += sum;
        }
        avg /= n;
        cout << fixed << setprecision(10) << avg << "\n";
    }
    
    return 0;
}
