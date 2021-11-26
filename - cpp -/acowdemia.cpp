
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//USACO - 2021 US Open Silver 3 - Acowdemia

//we have an h-index that we want to maximize using extra citations from survey essays. 

//my first thought was to binary search through the possible h-indexes, but to do that, we'll have to come up with a fast way of determining whether or
//not a given h-index is valid. 

//the way I came up with is as follows. First, you can presort the research papers in descending order, since you'll want to always use the research
//papers with the highest initial citation count. 

//then count out h papers, and see how many citations you need to add. If the total is less than or equal to k * l, and the maximum amount of citations you need
//for a single paper is less than or equal to k, then the corresponding h value is valid. 

//I have no idea why this works. 

bool isValid(ll val, ll k, ll l, vector<int> nums){
    ll citeLimit = (ll) k * (ll) l;
    ll sum = 0;
    ll maxDiff = 0;
    for(int i = nums.size() - 1; i >= (nums.size() - (int) val); i--){
        if(i == -1){
            break;
        }
        sum += (ll) max((ll) 0, (ll) (val - nums[i]));
        maxDiff = max(maxDiff, (ll) (val - nums[i]));
    }
    if(maxDiff > k || sum > citeLimit){
        return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k, l;
    cin >> n >> k >> l;
    vector<int> nums(n);
    for(int i = 0; i < n; i++){
        cin >> nums[i];
    }
    sort(nums.begin(), nums.end());
    ll low = 0;
    ll high = n;
    ll mid = low + (high - low) / 2;
    ll ans = 0;
    while(low <= high){
        //cout << "TESTING: " << mid << endl;
        if(isValid(mid, k, l, nums)){
            //cout << "VALID" << endl;
            ans = max(ans, mid);
            low = mid + 1;
        }
        else{
            //cout << "NOT VALID" << endl;
            high = mid - 1;
        }
        mid = low + (high - low) / 2;
    }
    cout << ans << endl;
    
    return 0;
}
