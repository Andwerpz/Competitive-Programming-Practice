#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1882C

//if the first element is positive, then you can take all the cards that are positive. 
//otherwise, you'll either have to take the first value, which is negative, or take only from the second
//value onwards. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<ll> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        ll psum = 0;
        for(int i = 0; i < n; i++){
            if(a[i] > 0){
                psum += a[i];
            }
        }
        ll aans = 0;
        ll bans = 0;
        {
            aans = psum;
            if(a[0] > 0){
                aans -= a[0];
            }
            if(n != 1 && a[1] > 0){
                aans -= a[1];
            }
        }
        {
            bans = psum;
            if(a[0] < 0){
                bans += a[0];
            }
        }
        cout << max(aans, bans) << "\n";
    }
    
    return 0;
}
