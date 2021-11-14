
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
        int a, b, c;
        cin >> a >> b >> c;
        int diff = std::abs((a + c) - b);
        cout << diff << endl;
    }

    return 0;
}



