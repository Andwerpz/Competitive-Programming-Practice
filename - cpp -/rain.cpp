#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1710B

//the key observation is that the highest points of the distribution are going to be at all of x[i]. 
//we just have to check each x[i] when removing the ith day. 

//to calculate the final distribution, we can save a running sum, and the slope of the distribution. 
//note that the slope only changes when we enter or exit a days 'range of influence', or we cross over the midpoint
//of a day. 

//checking each x[i] still will result in n^2 time complexity, so the optimization here is to save the maximum 
//x[i] to the left, and right, making it so you only need to check 2 x[i] every time. 

// - Calculate the final distribution

// - Calculate for each x[i], the maximum dist + height from left and right. 

// - Go through each x[i], and mark answers. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n, m;
        cin >> n >> m;
        vector<vector<int>> pos(n, vector<int>(3)); //x, p, initial index;
        vector<vector<int>> lr(n * 3, vector<int>(2)); //dx, pos
        vector<ll> a(n);
        vector<int> ans(n);
        for(int i = 0; i < n; i++){
            int x, p;
            cin >> x >> p;
            pos[i][0] = x;
            pos[i][1] = p;
            pos[i][2] = i;
            lr[i * 3 + 0][0] = 1;
            lr[i * 3 + 0][1] = x - p;
            lr[i * 3 + 1][0] = 1;
            lr[i * 3 + 1][1] = x + p;
            lr[i * 3 + 2][0] = -2;
            lr[i * 3 + 2][1] = x;
        }
        sort(pos.begin(), pos.end(), [](vector<int>& a, vector<int>& b) {return a[0] < b[0];});
        sort(lr.begin(), lr.end(), [](vector<int>& a, vector<int>& b) {return a[1] < b[1];});
        ll dx = 0;
        ll ptr = lr[0][1];
        ll aPtr = 0;
        ll sum = 0;
        for(int i = 0; i < lr.size(); i++){
            ll diff = lr[i][1] - ptr;
            ptr = lr[i][1];
            sum += dx * diff;
            dx += lr[i][0];
            if(lr[i][0] == -2){
                a[aPtr] = sum;
                aPtr ++;
            }
        }
        vector<ll> mR(n);
        vector<ll> mL(n);
        dx = 0;
        for(int i = 0; i < n; i++){
            if(dx == 0){
                if(a[i] > m){
                    dx = 1;
                    mR[i] = a[i] - m;
                }
            }
            else{
                mR[i] = max(mR[i - 1] + (pos[i][0] - pos[i - 1][0]), a[i] - m);
            }
        }
        dx = 0;
        for(int i = n - 1; i >= 0; i--){
            if(dx == 0){
                if(a[i] > m){
                    dx = 1;
                    mL[i] = a[i] - m;
                }
            }
            else{
                mL[i] = max(mL[i + 1] + (pos[i + 1][0] - pos[i][0]), a[i] - m);
            }
        }
        for(int i = 0; i < n; i++){
            int id = pos[i][2];
            if(pos[i][1] >= max(mR[i], mL[i])) {
                ans[id] = 1;
            }
            else{
                ans[id] = 0;
            }
        }
        for(int i : ans){
            cout << i;
        }
        cout << "\n";
    }
    
    return 0;
}
