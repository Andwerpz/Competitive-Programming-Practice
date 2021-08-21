
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long ll;

using namespace std;

//CSES - Two Sets

int main() {

    int n;
    cin >> n;
    ll sum = (((ll) n) * ((ll) n + 1)) / 2ll;
    if(sum % 2 == 1){
        cout << "NO\n";
    }
    else{
        cout << "YES\n";
        ll target = sum / 2;
        vector<int> dict;
        vector<int> dict2;
        ll curSum = 0;
        for(int i = n; i >= 1; i--){
            ll diff = target - curSum;
            if(i <= diff){
                dict.push_back(i);
                curSum += i;
            }
            else{
                dict2.push_back(i);
            }
        }
        cout << dict.size() << "\n";
        for(int i = 0; i < dict.size(); i++){
            cout << dict[i] << " ";
        }
        cout << "\n" << dict2.size() << "\n";
        for(int i = 0; i < dict2.size(); i++){
            cout << dict2[i] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}



