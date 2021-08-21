
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

int main() {

    int q;
    cin >> q;
    vector<ll> pfx;
    ll pointer = 10;
    ll increment = 9;
    ll sum = 0;
    while(sum <= 1e18){
        sum += pointer;
        if(pointer == 10){
            pointer *= 9;
        }
        else{
            pointer *= 10;
        }
        increment *= 10;
        pointer += increment;
        pfx.push_back(sum);
        //cout << sum << endl;
    }
    while(q-- > 0){
        ll k;
        cin >> k;
        ll numLength = 1;
        for(int i = 0; i < pfx.size(); i++){
            if(k > pfx[i]){
                numLength = i + 2;
            }
        }
        ll diff = k;
        ll base = 0;
        if(numLength != 1){
            base = 9;
            for(int i = 2; i < numLength; i++){
                base *= 10;
                base += 9;
            }
        }
        diff -= base;
        ll whichNum = base + (diff / numLength + (diff % numLength != 0? 1 : 0));
        string s = to_string(whichNum);
        ll offset = diff % numLength;
        //cout << "DIFF: " << diff << " OFFSET: " << offset << " NUM: " << whichNum << endl;
        if(offset == 0){
            cout << s[s.length() - 1] << endl;
        }
        else {
            cout << s[offset - 1] << endl;
        }
    }

    return 0;
}



