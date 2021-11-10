
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1561C

//each cave can be represented by the minimum amount of power required to pass the cave, and the number of monsters residing in the cave. Using those two numbers, 
//for any power level, you can determine whether you can pass the cave, and if you can, then what power you will be at when you exit the cave. 

//using this, we can easily test for any power level, whether they can pass all caves in O(n) time. We just have to prioritize caves in the order of lowest required power level
//and work your way up. 

//to solve, just do binary search.

using namespace std;

bool isValid(vector<vector<int>> caves, int val){
    int curPower = val;
    for(int i = 0; i < caves.size(); i++){
        if(caves[i][0] > curPower){
            return false;
        }
        curPower += caves[i][1];
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        //each cave described by minimum required power to clear, and num monsters
        vector<vector<int>> caves(n);
        for(int i = 0; i < n; i++){
            int k;
            cin >> k;
            vector<int> next(k);
            for(int j = 0; j < k; j++){
                cin >> next[j];
            }
            int pointer = next[k - 1] + 1;
            for(int j = k - 2; j >= 0; j--){
                pointer --;
                pointer = max(pointer, next[j] + 1);
            }
            caves[i] = {pointer, k};
        }
        sort(caves.begin(), caves.end(), [&](vector<int> a, vector<int> b) -> bool {return a[0] < b[0];});
        int high = 1000000001;
        int low = 2;
        int mid = low + (high - low) / 2;
        int ans = high;
        while(low <= high){
            if(isValid(caves, mid)){
                ans = min(ans, mid);
                high = mid - 1;
            }
            else{
                low = mid + 1;
            }
            mid = low + (high - low) / 2;
        }
        cout << ans << endl;
    }

    return 0;
}



