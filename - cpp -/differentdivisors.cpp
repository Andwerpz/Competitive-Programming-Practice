
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t-- > 0){
        int d;
        cin >> d;
        ll ans = 1;
        ans *= (ll) (1 + d);
        ans *= (ll) (1 + d + d);
        cout << ans << endl;
    }

    return 0;
}



