#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1711A

//if you sort all numbers in ascending order, and swap each with their neighbor, then 
//it is guaranteed that the index won't be able to divide the value, except for the value at index 1. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<int> ans(n);
        for(int i = 0; i < n; i++){
            ans[i] = i + 1;
        }
        for(int i = n % 2; i < n; i += 2){
            int tmp = ans[i];
            ans[i] = ans[i + 1];
            ans[i + 1] = tmp;
        }
        for(int i = 0; i < n; i++){
            cout << ans[i] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
