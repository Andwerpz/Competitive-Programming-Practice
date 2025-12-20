#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef long long ll;
typedef vector<ll> vl;
typedef vector<vi> vvi;
typedef vector<bool> vb;

//ICPC ECNA 2025 - I

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n; cin >> n;
    vector<vector<int>> a(n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j <= i; j++) {
            int x; cin >> x;
            a[i].push_back(x);
        }
    }

    int ok = 1;
    while(1) {
        int f = 0;
        for(int i = 0; i + 1 < n; i++) {
            for(int j = 0; j <= i; j++) {
                int cnt = 0;

                cnt += a[i][j] == 100;
                cnt += a[i+1][j] == 100;
                cnt += a[i+1][j+1] == 100;

                if(cnt == 0) {
                    if(a[i][j] != a[i+1][j] + a[i+1][j+1]) ok = 0;
                }

                if(cnt == 1) {
                    if(a[i][j] == 100) {
                        a[i][j] = a[i+1][j] + a[i+1][j+1];
                        if(abs(a[i][j]) >= 100) ok = 0;
                    }
                    if(a[i+1][j] == 100) {
                        a[i+1][j] = a[i][j] - a[i+1][j+1];
                        if(abs(a[i+1][j]) >= 100) ok = 0;
                    }
                    if(a[i+1][j+1] == 100) {
                        a[i+1][j+1] = a[i][j] - a[i+1][j];
                        if(abs(a[i+1][j+1]) >= 100) ok = 0;
                    }
                    f = 1;
                }

            }
        }
        if(!ok) break;
        if(!f) break;
    }

    if(!ok) {
        cout << "no solution\n";
    } else {
        int f = 0;
        for(int i = 0; i < n; i++) for(int x : a[i]) if(x == 100) f = 1;
        
        if(f) {
            cout << "ambiguous\n";
        } else {
            cout << "solvable\n";
            for(int i = 0; i < n; i++) {
                for(int x : a[i]) cout << x << " ";
                cout << '\n';
            }
        }
    }

    return 0;
}