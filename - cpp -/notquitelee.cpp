
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
    vector<int> nums(n);
    for(int i = 0; i < n; i++){
        cin >> nums[i];
    }
    vector<ll> powers(100);
    for(int i = 0; i < n; i++){
        int next = nums[i];
        ll power = 0;
        while(next % 2 == 0){
            power ++;
            next /= 2;
        }
        powers[power] ++;
        cout << nums[i] << " : " << power << endl;
    }
    
    for(ll i : powers){
        cout << i << " ";
    }
    
    return 0;
}
