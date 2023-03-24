#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 08 E

//checking whether or not you can split the array into 3 equal subarrays. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<ll> a(n);
    ll sum = 0;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        sum += a[i];
    }
    if(sum % 3 != 0){
        cout << "-1\n";
        return 0;
    }
    int ai = -1;
    int bi = -1;
    ll tgt = sum / 3;
    sum = 0;
    for(int i = 0; i < n; i++){
        sum += a[i];
        if(sum == tgt) {
            if(ai == -1){
                ai = i + 1;
            }
            else if(bi == -1) {
                bi = i + 1;
            }
            sum = 0;
        }
        else if(sum >= tgt){
            cout << "-1\n";
            return 0;
        }
    }
    cout << ai << " " << bi << "\n";
    
    return 0;
}
