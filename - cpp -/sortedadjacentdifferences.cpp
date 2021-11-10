
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1399B

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<int> nums(n);
        for(int i = 0; i < n; i++){
            cin >> nums[i];
        }
        sort(nums.begin(), nums.end());
        int l = n / 2 - 1;
        int r = l + 1; 
        while(true){
            if(r == n){
                break;
            }
            cout << nums[r] << " ";
            if(l < 0){
                break;
            }
            cout << nums[l] << " ";
            r ++;
            l --;
        }
        cout << endl;
    }

    return 0;
}



