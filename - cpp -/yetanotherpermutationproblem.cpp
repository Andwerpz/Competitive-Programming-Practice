#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1858C

//lets maintain a visited array, 'v', which keeps track of which numbers we've visited from 1 - n. 

//for each i in 1 - n in ascending order, first check if v[i]. If true, then move to the next one. 
//if false, then put i, i * 2, i * 4, i * 8, ... into the permutation, and mark them all as visited. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<bool> v(n + 1, false);
        vector<int> ans(0);
        for(int i = 1; i <= n; i++){
            if(v[i]){
                continue;
            }
            int ptr = i;
            while(ptr <= n && !v[ptr]) {
                v[ptr] = true;
                ans.push_back(ptr);
                ptr *= 2;
            }
        }
        for(int i = 0; i < n; i++){
            cout << ans[i] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
