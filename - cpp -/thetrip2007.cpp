#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//Kattis - trip2007

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    while(n != 0){
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        reverse(a.begin(), a.end());
        int k = 1;
        for(int i = 0; i < a.size(); i++){
            while(i + k < a.size() && a[i] == a[i + k]) {
                k ++;
            }
        }
        cout << k << "\n";
        for(int i = 0; i < k; i++){
            for(int j = i; j < a.size(); j += k){
                cout << a[j] << " ";
            }
            cout << "\n";
        }
        cin >> n;
    }
    
    return 0;
}
