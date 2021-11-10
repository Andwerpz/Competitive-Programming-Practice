
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1029B

//a good contest has to consist of consecutive problems, given that the problems are sorted ascending.

//if a problem is compatible with the problem after the next problem, then it also has to be compatible with the problem right next to it. It follows that the next problem
//has to be compatible with the problem after it as well.

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
    int ans = 1;
    int counter = 1;
    for(int i = 1; i < n; i++){
        int cur = nums[i];
        int prev = nums[i - 1];
        if(cur <= prev * 2){
            counter ++;
        }
        else{
            counter = 1;
        }
        ans = max(ans, counter);
    }
    cout << ans << endl;

    return 0;
}



