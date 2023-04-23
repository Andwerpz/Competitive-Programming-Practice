#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 13 D

//simulate the problem. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    ll t;
    cin >> t;
    ll a, b, c;
    cin >> a >> b >> c;
    vector<ll> time(n, 0);
    cin >> time[0];
    for(int i = 1; i < n; i++){
        time[i] = (time[i - 1] * a + b) % c + 1;
    }
    sort(time.begin(), time.end());
    ll sum = 0;
    ll nsolve = 0;
    ll penalty = 0;
    ll mod = 1e9 + 7;
    for(int i = 0; i < n; i++){
        //cout << time[i] << endl;
        sum += time[i];
        if(sum > t) {
            break;
        }
        nsolve ++;
        penalty += sum;
        penalty %= mod;
    }
    cout << nsolve << " " << penalty << "\n";
    
    return 0;
}
