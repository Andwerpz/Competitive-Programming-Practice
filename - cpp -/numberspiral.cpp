
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//CSES - Number Spiral

int main()
{

    int t, y, x;
    cin >> t;
    while(t-- > 0){
        cin >> y >> x;
        bool yLarger = y >= x;
        bool reverse;
        ll ans = 0;
        if(yLarger){
            reverse = y % 2 == 0;
            ll power;
            if(!reverse){
                power = (ll) (y - 1) * (y - 1);
                ans = power + (ll) x;
            }
            else{
                power = (ll) y * y;
                ans = power - (ll) (x - 1);
            }
        }
        else{
            reverse = x % 2 == 1;
            ll power;
            if(!reverse){
                power = (ll) (x - 1) * (x - 1);
                ans = power + (ll) y;
            }
            else{
                power = (ll) x * x;
                ans = power - (ll) (y - 1);
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}



