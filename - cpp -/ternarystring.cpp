
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1354B

//just use two pointers

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t-- > 0){
        string s;
        cin >> s;
        int n = s.length();
        int ans = -1;
        vector<int> nums(n);
        vector<int> counter(3);
        for(int i = 0; i < n; i++){
            nums[i] = s[i] - '1';
        }
        int pointer = 0;
        for(int i = 0; i < n; i++){
            int next = nums[i];
            counter[next] ++;
            while(counter[nums[pointer]] >= 2){
                counter[nums[pointer]] --;
                pointer ++;
            }
            if(counter[0] != 0 && counter[1] != 0 && counter[2] != 0){
                if(ans == -1){
                    ans = i - pointer + 1;
                }
                else{
                    ans = min(ans, i - pointer + 1);
                }
            }
        }
        cout << (ans == -1? 0 : ans) << endl;
    }

    return 0;
}



