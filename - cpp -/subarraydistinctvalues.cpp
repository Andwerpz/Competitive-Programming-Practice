
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//CSES 2428

//iterate a left pointer, and for each left movement, iterate the right pointer as far right as you can.

//each iteration, add to the ans r - l, as that's how many subarrays you can make starting at l. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    vector<int> nums(n);
    for(int i = 0; i < n; i++){
        cin >> nums[i];
    }
    map<int, int> m;
    int r = 0;
    ll ans = 0;
    for(int i = 0; i < n; i++){
        while(true){
            if(r >= n){
                break;
            }
            if(m.find(nums[r]) != m.end()){
                m[nums[r]]++;
            }
            else if(m.size() < k){
                m.insert({nums[r], 1});
            }
            else{
                break;
            }
            r++;
        }
        ans += r - i;
        int next = nums[i];
        if(m[next] == 1){
            m.erase(next);
        }
        else{
            m[next] --;
        }
        //cout << i << " " << r << endl;
    }
    cout << ans << endl;
    
    return 0;
}
