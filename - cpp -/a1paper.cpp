#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Lab 04 A

//the idea is to greedily use the largest sheets of paper possible. If you use two smaller pieces of paper as opposed
//to one larger sheet of paper that you already have, you're just wasting tape. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<ll> a(n);
    vector<double> length(n, 0);
    vector<double> width(n, 0);
    width[1] = pow(2.0, -5.0 / 4.0);
    length[1] = pow(2.0, -3.0 / 4.0);
    for(int i = 1; i < n; i++){
        cin >> a[i];
        if(i != 1){
            length[i] = width[i - 1];
            width[i] = length[i - 1] / 2.0;  
        }
        //cout << length[i] << " " << width[i] << "\n";
    }
    ll needed = 1;
    for(int i = 0; i < n; i++){
        a[i] = min(needed, a[i]);
        needed = max(needed - a[i], (ll) 0);
        needed *= 2;
    }
    if(needed != 0){
        cout << "impossible\n";
        return 0;
    }
    double ans = 0;
    for(int i = n - 1; i > 0; i--) {
        ans += (a[i] / 2) * length[i];
        a[i - 1] += a[i] / 2;
        //cout << "glue : " << a[i] << "\n";
    }
    cout << fixed << setprecision(10) << ans << "\n";
    
    return 0;
}
