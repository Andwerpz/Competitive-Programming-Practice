#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//AtCoder - ARC139A

//generate the values of array a from 1 to n. 
//for each, just greedily find the minimum value. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<ll> t(n);
    for(int i = 0; i < n; i++){
        cin >> t[i];
    }
    ll a = 0;
    for(int i = 0; i < n; i++){
        //cout << a << endl;
        ll pow = (1ll << t[i]);
        ll min = (a / pow) * pow;
        //cout << "MIN INIT : " << min << "\n";
        if(min <= a){
            min += pow;
        }
        if(min % (1ll << (t[i] + 1)) == 0){
            min += pow;
        }
        a = min;
    }
    cout << a << "\n";
    
    return 0;
}
