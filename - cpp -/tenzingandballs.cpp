#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1842C

//lets first try to find all the possible segments that can be removed. Once we have all the segments that can be removed, then we
//notice that the problem is just trying to find how to pick a set of disjoint segments such that the sum of the lengths is maximized. 

//one problem is that the number of segments can be around n^2. The second problem is that if we do have all the segments, how would we 
//even find the maximum length sum of a disjoint set of segments?

//both problems can be solved using dp. 
//dp[i][j] = maximum balls removed in the segment [0, i).
//if j == 1, then the previous move was a 'jump' where we removed balls. 
//else, the previous move was a 'skip' where we didn't remove a ball. 

//it's important to keep track of the previous move because we treat segment removal operations as right exclusive; when we remove the 
//segment from i to j, we remove all balls in [i, j), instead of [i, j] as specified by the problem. 
//this allows us to decide whether or not to remove the next segment, or stop removing. 

//if we decide to stop removing, we must then remove the ball that we are on, because we are still bound to remove [i, j]. 

//with this, we don't have to keep track of all of the segments, as from each index, we only have to keep track of the index of the next
//element with the same value. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        vector<int> nx(n, -1);
        vector<int> pv(n + 1, -1);
        for(int i = 0; i < n; i++){
            if(pv[a[i]] != -1){
                nx[pv[a[i]]] = i;
            }
            pv[a[i]] = i;
        }
        int unv = -1;
        vector<vector<int>> dp(n + 1, vector<int>(2, unv));
        dp[0][0] = 0;
        for(int i = 0; i < n; i++) {
            //prev was not jump
            {
                //don't jump
                dp[i + 1][0] = max(dp[i + 1][0], dp[i][0]);
                //jump
                if(nx[i] != -1){
                    int df = nx[i] - i;
                    dp[nx[i]][1] = max(dp[nx[i]][1], dp[i][0] + df);
                }
            }       
            //prev was jump
            if(dp[i][1] == unv) {
                continue;
            }
            {
                //don't jump
                dp[i + 1][0] = max(dp[i + 1][0], dp[i][1] + 1);
                //jump
                if(nx[i] != -1){
                    int df = nx[i] - i;
                    dp[nx[i]][1] = max(dp[nx[i]][1], dp[i][1] + df);
                }
            }
        }
        cout << dp[n][0] << "\n";
    }
    
    return 0;
}
