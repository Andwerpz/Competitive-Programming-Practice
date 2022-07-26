#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1701C

//binary search through finishing times. 

//to check whether a given time will work:
//initially assign each task to the worker that is proficient at it. 

//go through each worker and get the sum of tasks that they can't finish. 

//if you can assign these extra tasks to other workers, then the time is valid; 
//else it is not valid. 

bool isValid(vector<int> a, ll val){
    ll extra = 0;
    for(int i = 0; i < a.size(); i++){
        if(a[i] > val){
            extra += (ll) (a[i] - val);
        }
    }
    for(int i = 0; i < a.size(); i++){
        if(a[i] < val){
            extra -= (val - (ll) a[i]) / 2;
        }
    }
    return extra <= 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n, m;
        cin >> n >> m;
        vector<int> a(n);
        for(int i = 0; i < m; i++){
            int index;
            cin >> index;
            a[--index] ++;
        }
        int low = 0;
        int high = m * 2;
        int mid = low + (high - low) / 2;
        int ans = high;
        while(low <= high){
            if(isValid(a, mid)){
                high = mid - 1;
                ans = min(ans, mid);
            }
            else{
                low = mid + 1;
            }
            mid = low + (high - low) / 2;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
