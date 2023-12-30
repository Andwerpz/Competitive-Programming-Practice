#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Rocky Mountain Regional 2016 F

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int x1, x2; cin >> x1 >> x2;
    

    int crash = 0;

    vector<bool> t1s(11234567), t2s(11234567);

    int n1; cin >> n1;
    for (int i = 0; i < n1; ++i) {
        int x; cin >> x;
        t1s[x] = true;
    }
    int n2; cin >> n2;
    for (int i = 0; i < n2; ++i) {
        int x; cin >> x;
        t2s[x] = true;
    }
if (x2 < x1) {
    swap(x1, x2);
    swap(t1s, t2s);
}

    bool move1 = false, move2 = false;
    for (int i = 1; i <= 1e7; ++i) {
        if (t1s[i]) {
            move1 = !move1;
        }

        if (t2s[i]) {
            move2 = !move2;
        }

        if (move1) x1++;
        if (move2) x2++;

        if ((x1 + 5) > x2) {
            crash = i+1;
            break;
        }
    }


    if (crash) cout << "bumper tap at time " << crash << endl;
    else cout << "safe and sound" << endl;
    
    return 0;
}
