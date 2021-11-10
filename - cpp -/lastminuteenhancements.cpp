
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1466B

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
        bool expand = false;
        int ans = 1;
        for(int i = 1; i < n; i++){
            int diff = nums[i] - nums[i - 1];
            if(diff == 0){
                expand = true;
            }
            else if(diff == 1){
                ans ++;
            }
            else if(diff >= 2){
                ans ++;
                if(expand){
                    expand = false;
                    ans ++;
                }
            }
        }
        if(expand){
            ans ++;
        }
        cout << ans << endl;
    }

    return 0;
}



