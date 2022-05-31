#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1691D

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<ll> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        bool isValid = true;
        for(int i = 0; i < n; i++){
            if(a[i] > 0){
                ll sum = a[i];
                int r = i + 1;
                ll max = a[i];
                while(r != n){
                    sum += a[r];
                    max = std::max(max, a[r]);
                    if(a[r] > 0){
                        break;
                    }
                    r++;
                }
                //cout << sum << " " << max << endl;
                if(sum > max){
                    isValid = false;
                    break;
                }
            }
        }
        cout << (isValid? "YES\n" : "NO\n");
    }
    
    return 0;
}
