#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1620D

//lets say that you want to be able to do all numbers under x. Taking 3 1s, 3 2s, and floor(x / 3) 3s 
//will guarantee that you can produce all numbers less than or equal to x. 

//then, we can just brute force the number of 1s and 2s that we need to bring. 

int solve(vector<int>& a, int n1, int n2) {
    int ans = -1;
    for(int i = 0; i < a.size(); i++){
        int cmin = 1e9;
        for(int j = 0; j <= n1; j++){
            for(int k = 0; k <= n2; k++) {
                int next = a[i] - j - k * 2;
                if(next >= 0 && next % 3 == 0){
                    cmin = min(cmin, next / 3);
                }
            }
        }
        ans = max(ans, cmin);
    }
    ans += n1 + n2;
    //cout << "ANS : " << ans << " " << n1 << " " << n2 << "\n";
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        int ans = 1e9;
        for(int i = 0; i <= 3; i++){
            for(int j = 0; j <= 3; j++){
                ans = min(ans, solve(a, i, j));
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
