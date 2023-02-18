#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 05 E

//implementation. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    int ans = 0;
    while(n != 0){
        ans *= 2;
        if(n % 2 == 1){
            ans += 1;
        }
        n /= 2;
    }
    cout << ans << "\n";
    
    return 0;
}
