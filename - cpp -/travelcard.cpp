#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 756B

//2-parameter dp. For each time in ascending order, what is the minimum price after buying the instant, 90 mins, 1440 mins, or inheriting
//from a previous duration pass?

//updating the states after buying is pretty straightforwards, just take the minimum cost of the previous state, and tack
//on the cost of buying the repsective pass. 

//inheritance is a little trickier. What you need to do is find the oldest pass that you could have bought that would stil be valid
//at the current time. To do so, you can utilize binary search. 

int bsearch(int l, int r, vector<int>& t, int val){  //smallest index of value greater or equal to given val
    int low = l;
    int high = r;
    int mid = low + (high - low) / 2;
    int index = 1e9;
    while(low <= high){
        if(t[mid] >= val){
            index = min(index, mid);
            high = mid - 1;
        }
        else{
            low = mid + 1;
        }
        mid = low + (high - low) / 2;
    }
    return index;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<vector<int>> dp(n + 1, vector<int>(4, 1e9)); //inherit, buy instant, 90 mins, 1440 mins
    int ans = 0;
    dp[0][0] = 0;
    vector<int> t(n);
    for(int i = 1; i <= n; i++){
        cin >> t[i - 1];
        int prevMin = min(min(dp[i - 1][0], dp[i - 1][1]), min(dp[i - 1][2], dp[i - 1][3]));
        dp[i][1] = prevMin + 20;
        dp[i][2] = prevMin + 50;
        dp[i][3] = prevMin + 120;
        if(i == 1){ //nothing to inherit from
            //cout << dp[i][1] << " " << dp[i][2] << " " << dp[i][3] << endl;
            int curAns = min(min(dp[i][0], dp[i][1]), min(dp[i][2], dp[i][3]));
            cout << (curAns - ans) << "\n";
            ans = curAns;
            continue;
        }
        //bsearch for inherit
        int a = bsearch(0, i - 1, t, t[i - 1] - 89);
        int b = bsearch(0, i - 1, t, t[i - 1] - 1439);
        //cout << "I: " << i << " " << a << " " << b << "\n";
        dp[i][0] = min(dp[a + 1][2], dp[b + 1][3]);
        //cout << dp[i][0] << " " << dp[i][1] << " " << dp[i][2] << " " << dp[i][3] << endl;
        int curAns = min(min(dp[i][0], dp[i][1]), min(dp[i][2], dp[i][3]));
        cout << (curAns - ans) << "\n";
        ans = curAns;
    }
    
    return 0;
}
