#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1850B

//take the max out of all entries that have less than or equal to 10 words. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        int mx = -1;
        int mxind = -1;
        for(int i = 0; i < n; i++){ 
            int a, b;
            cin >> a >> b;
            if(a > 10){
                continue;
            }
            if(b > mx){
                mx = b;
                mxind = i;
            }
        }
        cout << (mxind + 1) << "\n";
    }
    
    return 0;
}
