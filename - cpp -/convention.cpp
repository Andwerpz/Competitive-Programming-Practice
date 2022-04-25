
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//USACO Silver December 2018

//For this one, we can binary search over the maximum allowed waiting time. 
//If we sort the array of cow arrival times, we can test whether a predetermined 
//maximum waiting time is possible in linear time via greedy algorithm. 

//Obviously, if a waiting time t works, then t + 1 has to work as well. 

bool isValid(vector<int> nums, int m, int c, int maxWait){
    int depart = -1;
    int bus = 0;
    int capacity = 0;
    for(int i = 0; i < nums.size(); i++){
        if(nums[i] > depart || capacity == c){
            bus ++;
            capacity = 1;
            depart = nums[i] + maxWait;
        }
        else {
            capacity ++;
        }
    }
    return bus <= m;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("convention.in", "r", stdin);
	freopen("convention.out", "w", stdout);

    int n, m, c;
    cin >> n >> m >> c;
    vector<int> nums(n);
    for(int i = 0; i < n; i++){
        cin >> nums[i];
    }
    sort(nums.begin(), nums.end(), [] (int a, int b) {return a < b;});
    int low = 0;
    int high = 1e9;
    int mid = low + (high - low) / 2;
    int ans = 1e9;
    while(low <= high){
        if(isValid(nums, m, c, mid)){
            ans = min(ans, mid);
            high = mid - 1;
        }
        else{
            low = mid + 1;
        }
        mid = low + (high - low) / 2;
    }
    cout << ans;
    
    return 0;
}
