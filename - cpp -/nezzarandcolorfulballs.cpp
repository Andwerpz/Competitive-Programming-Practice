
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1478A

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
        int maxSame = 0;
        int counter = 0;
        int prev = 0;
        for(int i = 0; i < n; i++){
            if(i != 0){
                if(prev != nums[i]){
                    counter = 0;
                }
            }
            prev = nums[i];
            counter ++;
            maxSame = max(maxSame, counter);
        }
        cout << maxSame << endl;
    }

    return 0;
}



