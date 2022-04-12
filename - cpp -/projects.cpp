
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//CSES 1140

//a naive strategy to solve this problem is to maintain a dp arr of length l, where l is the maximum
//end date of any project. For each day, dp[i] = max(dp[i], dp[i - 1]), and if there is a project, 
//dp[i + a] = max(dp[i + a], dp[i]), where a is the length of the project. 

//the problem with the naive strategy is that l = 1e9, which exceeds time and mem limit. Notice that the only 
//days we actually need to care about are the days with project starts. Every other day we can discard. 

//sort the projects in ascending order based on start day. For each project, we want to calculate the max money
//we can get before that project.

//to update other projects after using the current one, synonomous to dp[i + a] in the naive solution, we do a
//bin search to find the earliest project that has a start time greater than the current projects end time, and update
//that projects value. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<ll> dp(n + 1);
    vector<vector<int>> times(n + 1, vector<int>(3));
    for(int i = 0; i < n; i++){
        cin >> times[i][0] >> times[i][1] >> times[i][2];
    }
    times[n][0] = 1e9 + 7;
    times[n][1] = 1e9 + 7;
    sort(times.begin(), times.end(), [](const vector<int>& a, const vector<int>& b){return a[0] < b[0];});
    for(int i = 0; i < n; i++){
        int end = times[i][1];
        ll curVal = dp[i];
        ll r = times[i][2];
        //bin search for earliest starting day greater than cur ending day
        int low = i + 1;
        int high = n;
        int mid = low + (high - low) / 2;
        int ans = high;
        while(low <= high){
            if(times[mid][0] > end){
                ans = min(ans, mid);
                high = mid - 1;
            }
            else{
                low = mid + 1;
            }
            mid = low + (high - low) / 2;
        }
        dp[ans] = max(dp[ans], curVal + r);
        dp[i + 1] = max(dp[i + 1], dp[i]);
        //cout << times[i][0] << " ";
    }
    //cout << endl;
    cout << dp[n] << endl;
    
    return 0;
}
