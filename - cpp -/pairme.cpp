
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codechef - SUMPOS

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t-- > 0){
        vector<int> nums(3);
        bool isValid = false;
        int sum = 0;
        for(int i = 0; i < 3; i++){
            cin >> nums[i];
            sum += nums[i];
        }
        for(int i = 0; i < 3; i++){
            if(sum % nums[i] == 0 && sum / nums[i] == 2){
                isValid = true;
                break;
            }
        }
        cout << (isValid? "YES\n" : "NO\n");
    }

    return 0;
}



