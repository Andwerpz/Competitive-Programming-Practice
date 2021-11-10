
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

    int n;
    cin >> n;
    vector<ll> pfx(n);
    vector<ll> nums(n);
    for(int i = 0; i < n; i++){
        cin >> pfx[i];
        nums[i] = pfx[i];
        if(i % 2 == 1){
            pfx[i] = -pfx[i];
        }
        if(i != 0){
            pfx[i] += pfx[i - 1];
        }
        cout << pfx[i] << " ";
    }
    cout << endl;
    ll ans = 0;
    for(int i = 0; i < n; i += 2){
        for(int j = i + 1; j < n; j += 2){
            if(j == i + 1){
                ans += (ll) min(nums[i], nums[j]);
            }
            else{
                
            }
        }
    }
    cout << ans << endl;

    return 0;
}



