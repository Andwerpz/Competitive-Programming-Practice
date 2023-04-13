#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 847C

//notice that if you have n pairs of brackets, then the maximum sum you can make is n * (n - 1) / 2. 
//also notice that you can make any sum less than the maximum as well. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, k;
    cin >> n >> k;
    if(n * (n - 1) / 2 < k){
        cout << "Impossible\n";
        return 0;
    }
    vector<ll> a(n, 0);
    ll sum = n * (n - 1) / 2;
    for(int i = 0; i < n; i++){
        a[i] = i;
    }
    for(int i = n - 1; i >= 0; i--){
        ll d = min(sum - k, a[i]);
        a[i] -= d;
        sum -= d;
    }
    a.push_back(0);
    for(int i = 0; i < n; i++){
        if(i != 0){
            if(a[i - 1] < a[i] && a[i + 1] <= a[i]){
                cout << "()";
            }
            else if(a[i - 1] > a[i] && a[i + 1] < a[i]){
                cout << "()";
            }
        }
        if(a[i + 1] > a[i]){
            for(int j = a[i]; j < a[i + 1]; j++){
                cout << "(";
            }
        }
        else if(a[i + 1] < a[i]){
            for(int j = a[i + 1]; j < a[i]; j++){
                cout << ")";
            }
        }
        else {
            cout << "()";
        }
    }
    cout << "\n";
    
    return 0;
}
