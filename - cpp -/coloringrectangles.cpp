
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//Codeforces - 1589B

//just greedily separate the grid into tiles of 3

int getAns(int l, int w){
    int ans = w * (l / 3);
    int remainder = l % 3;
    int across = w / 3 + (w % 3 == 0? 0 : 1);
    ans += remainder * across;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t-- > 0){
        int n, m;
        cin >> n >> m;
        int ans = min(getAns(n, m), getAns(m, n));
        cout << ans << endl;
    }

    return 0;
}
