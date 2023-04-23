#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//TAMU Spring 2023 Programming Contest B

//i didn't really prove it, just observed from online graphing calculators

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    if(n % 2 == 1){
        cout << n << "\n";
    }
    else {
        cout << n * 2 << "\n";
    }
    
    return 0;
}
