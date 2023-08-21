#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1854A2

//count the number of positive numbers, 'pcnt' and negative numbers, 'ncnt'. 

//if max(pcnt, ncnt) <= 12, then we can do the same routine that we did for the easy version. 

//otherwise, lets assume that pcnt > ncnt. The steps are very similar in the case where ncnt > pcnt. 
//choose any positive number (> 0), and add itself to itself until the value becomes greater than or equal to 20. 
//then, add this value to every negative number, and finally, do the prefix sum. 

//the maximum amount of steps required to generate a number >= 20 is 5, and there are maximum 7 negative elements. 
//doing the prefix sum routine takes 19 steps, so in total, this takes 31 steps at most. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n);
        int pcnt = 0;
        int ncnt = 0;
        for(int i = 0; i < n; i++){
            cin >> a[i];
            pcnt += a[i] > 0;
            ncnt += a[i] < 0;
        }
        if(pcnt + ncnt == 0){
            cout << "0\n";
            continue;
        }
        vector<pair<int, int>> ops;
        if(pcnt >= ncnt) {
            if(ncnt >= 8) {
                int mxAbs = abs(a[0]);
                int mxInd = 0;
                for(int i = 0; i < n; i++){
                    if(mxAbs < abs(a[i])) {
                        mxAbs = abs(a[i]);
                        mxInd = i;
                    }
                }
                bool neg = a[mxInd] < 0;
                for(int i = 0; i < n; i++){
                    if((a[i] < 0) != neg) {
                        ops.push_back({i, mxInd});
                    }
                }
                if(neg) {
                    for(int i = n - 1; i >= 1; i--){
                        ops.push_back({i - 1, i});
                    }
                }
                else {
                    for(int i = 0; i < n - 1; i++){
                        ops.push_back({i + 1, i});
                    }
                }
            }
            else {
                int pind = 0;
                for(int i = 0; i < n; i++){
                    if(a[i] > 0){
                        pind = i;
                        break;
                    }
                }
                for(int i = 0; i < 5; i++){
                    ops.push_back({pind, pind});
                }
                for(int i = 0; i < n; i++){
                    if(a[i] < 0){
                        ops.push_back({i, pind});
                    }
                }
                for(int i = 0; i < n - 1; i++){
                    ops.push_back({i + 1, i});
                }
            }
        }
        else {
            if(pcnt >= 8) {
                int mxAbs = abs(a[0]);
                int mxInd = 0;
                for(int i = 0; i < n; i++){
                    if(mxAbs < abs(a[i])) {
                        mxAbs = abs(a[i]);
                        mxInd = i;
                    }
                }
                bool neg = a[mxInd] < 0;
                for(int i = 0; i < n; i++){
                    if((a[i] < 0) != neg) {
                        ops.push_back({i, mxInd});
                    }
                }
                if(neg) {
                    for(int i = n - 1; i >= 1; i--){
                        ops.push_back({i - 1, i});
                    }
                }
                else {
                    for(int i = 0; i < n - 1; i++){
                        ops.push_back({i + 1, i});
                    }
                }
            }
            else {
                int nind = 0;
                for(int i = 0; i < n; i++){
                    if(a[i] < 0){
                        nind = i;
                        break;
                    }
                }
                for(int i = 0; i < 5; i++){
                    ops.push_back({nind, nind});
                }
                for(int i = 0; i < n; i++){
                    if(a[i] > 0){
                        ops.push_back({i, nind});
                    }
                }
                for(int i = n - 1; i >= 1; i--){
                    ops.push_back({i - 1, i});
                }
            }
        }
        cout << ops.size() << "\n";
        for(int i = 0; i < ops.size(); i++){
            cout << (ops[i].first + 1) << " " << (ops[i].second + 1) << "\n";
        }
    }
    
    return 0;
}
