
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//CSES 1630

//you can imagine the this problem as sampling from a bunch of linear functions in the form y = -x + (deadline - duration)

//notice that although you can't change the functions, you can change where you sample them, and since the 
//slope is negative for each, it will always be good to sample the functions at an earlier point. 

//thus, the solution is to do the tasks, shortest to longest duration. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<vector<ll>> nums(n);    //duration, deadline
    for(int i = 0; i < n; i++){
        int a, b;
        cin >> a >> b;
        nums[i] = vector<ll> {a, b};
    }
    ll ans = 0;
    ll curTime = 0;
    sort(nums.begin(), nums.end(), [](const vector<ll>& a, const vector<ll>& b){return a[0] < b[0];});    //sort by duration
    for(int i = 0; i < n; i++){
        curTime += nums[i][0];
        ans += nums[i][1] - curTime;
    }
    cout << ans << endl;
    
    return 0;
}
