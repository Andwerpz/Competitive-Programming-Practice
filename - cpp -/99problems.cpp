#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Lab 02 B

//you just have to check the 99 below and above n. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    int l = (n / 100) * 100 - 1;
    int h = (n / 100) * 100 + 99;
    int ans = l;
    if(abs(n - l) >= abs(n - h) || l < 0){
        ans = h;
    }
    cout << ans << "\n";
    
    return 0;
}
