#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1909B

//note that if we choose k = 2, then at most, we'll get 2 distinct values. 

//in the case where we get 1 distinct value, (all of the elements are even or odd), we can just set k to 4
//and we know that we'll get again at most 2 distinct values. 

//eventually, if we make k large enough, we'll always get 2 distinct values. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<ll> a(n);
        for(int i = 0; i < n; i ++){
            cin >> a[i];
        }
        ll k = 2;
        while(true){
            set<ll> s;
            for(int i = 0; i < n; i++){
                s.insert(a[i] % k);
            }
            if(s.size() == 2){
                break;
            }
            k *= 2;
        }
        cout << k << "\n";
    }
    
    return 0;
}
