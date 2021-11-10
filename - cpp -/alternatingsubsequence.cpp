
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1343C

//notice that since there are no 0s, the array can be split up into segments that are either negative or non-negative. In order to construct the maximum
//size subsequence that is alternating, we must take 1 value from each segment. 

//To maximize the sum of the longest subsequence is suddenly straightforward. We just need to take the maximum value from each segment.

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
        ll ans = 0;
        ll max = 0;
        bool negative = false;
        for(int i = 0; i < n; i++){
            int next;
            cin >> next;
            if(i == 0){
                negative = next < 0;
                max = next;
            }
            else{
                bool curNegative = next < 0;
                if(negative != curNegative){
                    negative = curNegative;
                    ans += max;
                    max = next;
                }
                else{
                    max = std::max(max, (ll) next);
                }
            }
        }
        ans += max;
        cout << ans << endl;
    }

    return 0;
}



