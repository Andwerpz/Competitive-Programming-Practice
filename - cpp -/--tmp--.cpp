#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
#define pb push_back
#define gl getline
double inf = numeric_limits<double>::infinity();
double EPS = 1e-9;
 
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
 
    /*
        greedy approach, start from greatest value and move left until our rolling sum == the value we need
 
        the "value we need" is just sum(1, n] / 2 aka n(n+1)/2
    */
 
    ll n;
    cin >> n;
    ll total = n * (n + 1) / 2;
    if (total % 2 == 1) {
        cout << "NO" << endl;
        return 0;
    }
 
    ll goal = total / 2;
    vector<int> vals(n, -1);
    for (int i = 0; i < n; i++) {
        vals[i] = i + 1;
    }
 
    ll rolling_sum = 0;
    ll ctr = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (rolling_sum + vals[i] <= goal) {
            rolling_sum += vals[i];
            ctr++;
            vals[i] = -1;
        }
    }
 
    if (rolling_sum != goal) {
        cout << "NO" << endl;
        return 0;
    }
 
    cout << "YES" << endl;
    cout << n - ctr << endl;
    for (int i = 0; i < n - 1; i++) {
        if (vals[i] != -1) {
            cout << vals[i] << " ";
        }
    }
    if (vals[n - 1] != -1) {
        cout << vals[n - 1];
    }
 
    cout << endl << ctr << endl;
    for (int i = 0; i < n - 1; i++) {
        if (vals[i] == -1) {
            cout << i + 1 << " ";
        }
    }
    if (vals[n - 1] == -1) {
        cout << n;
    }
    cout << endl;
 
    return 0;
}