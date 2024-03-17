#include <bits/stdc++.h>
typedef long long ll;
// typedef __int128 lll;
typedef long double ld;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1943A

//lets say that alice aims to have a mex of X. On her first move, it's always optimal to take a number
//that has the least frequency. 

//then, she can observe the number that bob removes, and just take that number on her next turn. As long as there
//is only 1 element that she has to take with a frequency of 1, then she can always reach her goal. 
//Obviously, if there is an element of frequency 0, she can never reach her goal. 

bool is_valid(vector<int>& f, int val) {
    vector<int> a(0);
    for(int i = 0; i < val; i++){
        a.push_back(f[i]);
    }
    sort(a.begin(), a.end());
    if((a.size() >= 1 && a[0] == 0) || a.size() >= 2 && (a[0] == 0 || a[1] <= 1)){
        return false;
    }
    return true;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n);
        vector<int> f(n, 0);
        for(int i = 0; i < n; i++){
            cin >> a[i];
            f[a[i]] ++;
        }
        int low = 0;
        int high = n; 
        int ans = low;
        while(low <= high){
            int mid = low + (high - low) / 2;
            if(is_valid(f, mid)) {
                ans = max(ans, mid);
                low = mid + 1;
            }
            else {
                high = mid - 1;
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
