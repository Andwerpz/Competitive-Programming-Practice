#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1699C

//lets say you had a permutation: 0 2 5 3 4 1.

//notice that you can change the middle part of the permutation: 2 5 3 4, to whatever you
//want, and they will remain similar. 

//this is because in order to get a mex of 2, the mex will necessarily have to be equal to 6. 

//to simplify, as long as a number is 'contained' within two smaller numbers, it is similar. 
//(this is a pretty bad explanation). 

//go check out the tutorial, idk how to explain the algorithm in an intuitive way. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        if(n == 1){
            cout << "1\n";
            continue;
        }
        vector<int> id(n);
        for(int i = 0; i < n; i++){
            id[a[i]] = i;
        }
        int l = min(id[0], id[1]);
        int r = max(id[0], id[1]);
        ll mod = 1e9 + 7;
        ll ans = 1;
        ll edge = 2;
        ll cnt = 0;
        for(int i = 2; i < n; i++){
            if(l < id[i] && id[i] < r){
                ll dist = r - l + 1;
                ans *= (dist - edge - cnt);
                ans %= mod;
                cnt ++;
            }
            else{
                l = min(l, id[i]);
                r = max(r, id[i]);
                edge ++;
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
