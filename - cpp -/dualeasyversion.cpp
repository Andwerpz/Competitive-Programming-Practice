#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1854A1

//first, find the element with the largest absolute value. Then, add this element to every element in the array. 

//after you do this, all the elements are either non-negative, or non-positive. 

//if they are positive, just do a prefix sum, if they are negative, then do a suffix sum. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n);
        int sum = 0;
        for(int i = 0; i < n; i++){
            cin >> a[i];
            sum += a[i];
        }
        vector<pair<int, int>> ops;
        if(sum >= 0){
            int prev = -1;
            for(int i = 0; i < n; i++){
                if(a[i] >= 0){
                    if(prev != -1){
                        ops.push_back({i, prev});
                    }
                    prev = i;
                }
            }
            ops.push_back({0, prev});
            ops.push_back({0, prev});
            for(int i = 1; i < n; i++){
                if(a[i] < 0){
                    ops.push_back({i, i - 1});
                    ops.push_back({i, i - 1});
                }
                else {
                    ops.push_back({i, i - 1});
                }
            }
        }
        else {
            reverse(a.begin(), a.end());
            for(int i = 0; i < n; i++){
                a[i] *= -1;
            }
            int prev = -1;
            for(int i = 0; i < n; i++){
                if(a[i] >= 0){
                    if(prev != -1){
                        ops.push_back({i, prev});
                    }
                    prev = i;
                }
            }
            ops.push_back({0, prev});
            ops.push_back({0, prev});
            for(int i = 1; i < n; i++){
                if(a[i] < 0){
                    ops.push_back({i, i - 1});
                    ops.push_back({i, i - 1});
                }
                else {
                    ops.push_back({i, i - 1});
                }
            }
            for(int i = 0; i < ops.size(); i++){
                ops[i].first = n - 1 - ops[i].first;
                ops[i].second = n - 1 - ops[i].second;
            }
        }
        cout << ops.size() << "\n";
        for(int i = 0; i < ops.size(); i++){
            cout << (ops[i].first + 1) << " " << (ops[i].second + 1) << "\n";
        }
    }
    
    return 0;
}
