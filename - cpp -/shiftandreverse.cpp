#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//AtCoder - ARC132B

//you can think of the array as a circular array, the shift operation just moves your view one element forwards, 
//and the reverse operation reverses your view. 

//thus, you just need to find the minimum amount of shift operations to make the array ascending or descending, and then
//apply the reverse operation if needed. 

int solve(vector<int>& a) {
    int ind = 0;
    for(int i = 0; i < a.size(); i++){
        if(a[i] == 1) {
            ind = i;
            break;
        }
    }
    if(a[(ind + 1) % a.size()] != 2) {
        return ind + 2;
    }
    return ind;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    int ans = solve(a);
    reverse(a.begin(), a.end());
    ans = min(ans, solve(a) + 1);
    cout << ans << "\n";
    
    return 0;
}
