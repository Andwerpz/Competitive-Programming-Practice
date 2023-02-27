#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 06 E

//figuring out how exactly each priest will vote might seem challenging, but it's pretty easy. 

//you have to process the priests in the opposite order, since the last priest isn't influenced by any other ones. 

//for each priest, figure out for each current state of the 3 tiles, what tile they will flip. 
//for the first priest, it's pretty easy, since they directly affect the outcome, but the second priest
//has to look at the outcomes for the first priest in order to make his decision. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<map<int, int>> a(n, map<int, int>());
        for(int i = 0; i < n; i++){
            for(int j = 0; j < 8; j++){
                int next;
                cin >> next;
                next --;
                a[i].insert({j, next});
            }
        }
        reverse(a.begin(), a.end());
        vector<vector<int>> dp(n + 1, vector<int>(8, 0));
        for(int i = 0; i < 8; i++){
            dp[0][i] = i;
        }
        for(int i = 1; i <= n; i++){
            for(int j = 0; j < 8; j++){
                int move = 1;
                int pref = a[i - 1].find(dp[i - 1][(j ^ move)]) -> second;
                for(int k = 0; k < 3; k++){
                    int nPref = a[i - 1].find(dp[i - 1][(j ^ (1 << k))]) -> second;
                    if(nPref < pref){
                        move = (1 << k);
                        pref = nPref;
                    }
                }
                dp[i][j] = dp[i - 1][(j ^ move)];
                //cout << dp[i][j] << " ";
            }
            //cout << "\n";
        }
        for(int i = (1 << 2); i > 0; i /= 2){
            if((dp[n][0] & i) != 0){
                cout << "Y";
            }
            else {
                cout << "N";
            }
        }
        cout << "\n";
    }
    
    return 0;
}
