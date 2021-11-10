
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1466A

//just loop through all the possible base lengths for the pasture

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
        set<int> dict;
        for(int i = 0; i < n; i++){
            for(int j = i + 1; j < n; j++){
                int diff = nums[j] - nums[i];
                if(dict.find(diff) == dict.end()){
                    dict.insert(diff);
                }
            }
        }
        cout << dict.size() << endl;
    }

    return 0;
}



