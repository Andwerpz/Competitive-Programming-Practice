
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1283B

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t-- > 0){
        int n, k;
        cin >> n >> k;
        int extra = k / 2;
        int ans = (n / k) * k;
        n -= ans;
        ans += min(n, extra);
        cout << ans << endl;
    }

    return 0;
}



