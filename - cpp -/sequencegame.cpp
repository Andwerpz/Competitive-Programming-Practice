#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1862B

//if b[i] >= b[i - 1], then b[i] could be in the original sequence. 
//otherwise, we need to 'fix' the original sequence by first adding a duplicate of b[i]. 

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
        vector<int> ans(0);
        ans.push_back(a[0]);
        for(int i = 1; i < n; i++){
            if(a[i] < a[i - 1]) {
                ans.push_back(a[i]);
            }
            ans.push_back(a[i]);
        }
        cout << ans.size() << "\n";
        for(int i = 0; i < ans.size(); i++){
            cout << ans[i] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
