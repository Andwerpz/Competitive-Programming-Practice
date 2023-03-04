#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1799B

//note that if a and b are positive integers, then ceil(a / b) = 1 is only true when a = b = 1. 
//thus if there is a 1 in the array, and not all numbers are 1, then it is impossible to make all the values equal. 

//if it is possible, always divide large numbers with smaller numbers, never divide two same numbers which will create
//a 1. 

int ceilDiv(int a, int b) {
    return a / b + (a % b == 0? 0 : 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<int> a(n, 0);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        int minInd = 0;
        int minVal = a[0];
        int maxInd = 0;
        int maxVal = a[0];
        for(int i = 0; i < n; i++){
            if(a[i] < minVal) {
                minInd = i;
                minVal = a[i];
            }
            if(a[i] > maxVal) {
                maxInd = i;
                maxVal = a[i];
            }
        }
        if(minVal == 1 && maxVal != 1){
            cout << "-1\n";
            continue;
        }
        //uh, this dumb D:
        vector<pair<int, int>> ans(0);
        while(true) {
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    while(a[i] > a[j]){
                        ans.push_back({i + 1, j + 1});
                        a[i] = ceilDiv(a[i], a[j]);
                    }
                }
            }
            bool isValid = true;
            for(int i = 0; i < n - 1; i++){
                if(a[i] != a[i + 1]){
                    isValid = false;
                    break;
                }
            }
            if(isValid){
                break;
            }
        }
        cout << ans.size() << "\n";
        for(int i = 0; i < ans.size(); i++){
            cout << ans[i].first << " " << ans[i].second << "\n";
        }
    }
    
    return 0;
}
