
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//Codeforces - 1589A

//x and y are equal to -u^2 and v^2

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t-- > 0){
        ll u, v;
        cin >> u >> v;
        cout << -(u * u) << " " << (v * v) << endl;
    }

    return 0;
}
