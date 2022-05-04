#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 903C

//the ans is just to take the max of any one size of box. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> nums(n);
    for(int i = 0; i < n; i++){
        cin >> nums[i];
    }
    vector<int> c(1e5);
    int p = 0;
    sort(nums.begin(), nums.end(), [] (int a, int b) {return b < a;});
    c[0] = 1;
    for(int i = 1; i < n; i++){
        if(i != 0 && nums[i] < nums[i - 1]){
            p++;
        }
        c[p] ++;
    }
    int ans = 0;
    for(int i : c){
        ans = max(ans, i);
    }
    cout << ans << endl;
    
    return 0;
}
