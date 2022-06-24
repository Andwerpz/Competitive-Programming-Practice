#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1686C

//why does this work?

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        if(n % 2 == 1){
            cout << "NO\n";
            continue;
        }
        bool isValid = true;
        vector<int> ans(0);
        for(int i = 0; i < n / 2; i++){
            ans.push_back(a[i]);
            ans.push_back(a[i + (n / 2)]);
        }
        for(int i = 0; i < n; i++){
            int prev = i == 0? ans[n - 1] : ans[i - 1];
            int next = i == n - 1? ans[0] : ans[i + 1];
            if((prev <= ans[i] && ans[i] <= next) || (prev >= ans[i] && ans[i] >= next)){
                isValid = false;
                break;
            }
        }
        cout << (isValid? "YES\n" : "NO\n");
        if(isValid){
            for(int i : ans){
                cout << i << " ";
            }
            cout << "\n";
        }
    }
    
    return 0;
}
