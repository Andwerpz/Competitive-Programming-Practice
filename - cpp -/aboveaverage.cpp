#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 13 A

//implementation

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        ld sum = 0;
        vector<ld> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
            sum += a[i];
        }
        sum /= (ld) n;
        ld cnt = 0;
        for(int i = 0; i < n; i++){
            if(a[i] > sum) {
                cnt ++;
            }
        }
        cnt = (cnt / (ld) n) * 100.0;
        cout << fixed << setprecision(3) << cnt << "%\n";
    }
    
    return 0;
}
