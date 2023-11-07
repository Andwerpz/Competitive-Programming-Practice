#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//AtCoder - ARC137B

//note that flipping a 0 will increase the sum by 1, and flipping a 1 will decrease the sum
//by one. 

//so the operation will just change the sum by the amount of 0s minus the amount of 1s. 

//thus, we can find the maximum and minimum possible change, and it's possible to get all the
//changes in the middle. 

int find_max(vector<int>& a) {
    int ans = 0;
    int sum = 0;
    for(int i = 0; i < a.size(); i++){
        sum += a[i];
        if(a[i] > sum) {
            sum = a[i];
        }
        ans = max(ans, sum);
    }
    return ans;
}

int find_min(vector<int>& a) {
    int ans = 0;
    int sum = 0;
    for(int i = 0; i < a.size(); i++){
        sum += a[i];
        if(a[i] < sum) {
            sum = a[i];
        }
        ans = min(ans, sum);
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
        if(a[i] == 0){
            a[i] = 1;
        }
        else {
            a[i] = -1;
        }
    }
    cout << find_max(a) - find_min(a) + 1 << "\n";
    
    return 0;
}
