
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1326B

//the x array represents the prefix maximum. 

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
    int curMax = 0;
    for(int i = 0; i < n; i++){
        int next = nums[i];
        cout << (next + curMax) << " ";
        next += curMax;
        curMax = max(next, curMax);
    }
    cout << endl;

    return 0;
}



