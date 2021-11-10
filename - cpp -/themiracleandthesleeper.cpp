
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1562A

//always set a to be the largest value: r. The minimum that b can be is 1/2 a + 1. If l is greater than that limit, then b = l.

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t-- > 0){
        int l, r;
        cin >> l >> r;
        int minB = max(r / 2 + 1, l);
        cout << r - minB << endl;
    }

    return 0;
}



