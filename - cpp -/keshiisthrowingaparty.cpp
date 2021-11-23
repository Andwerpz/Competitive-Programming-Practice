
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//Codeforces - 1610C

//binary search through the amount of people. 

//when testing if a given amount of people is valid, greedily select people from the poorest to the richest. When selecting people, always make sure to
//leave enough slots open so that you can fit in the amount of people you want to test. 

bool isValid(int val, vector<int> higher, vector<int> lower){
    //cout << "VAL: " << val << endl;
    int amt = 0;
    for(int i = 0; i < higher.size(); i++){
        int nextLim = min((int) higher.size() - i - 1, higher[i]);
        if(nextLim >= val - amt - 1 && lower[i] >= amt){
            //cout << i << endl;
            amt ++;
        }
    }
    //cout << "AMT : " << amt << endl;
    return amt >= val;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<int> higher(n);
        vector<int> lower(n);
        for(int i = 0; i < n; i++){
            cin >> higher[i] >> lower[i];
        }
        int ans = 0;
        int low = 0;
        int high = n;
        int mid = low + (high - low) / 2;
        while(low <= high){
            if(isValid(mid, higher, lower)){
                ans = max(ans, mid);
                low = mid + 1;
            }
            else{
                high = mid - 1;
            }
            mid = low + (high - low) / 2;
        }
        cout << ans << endl;
    }
    
    return 0;
}
