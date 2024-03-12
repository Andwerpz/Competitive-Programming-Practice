#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1919C

//kinda greedy, but idk why exactly it works. 

//for each of the sequences, maintain the last element so far in the sequence. 
//then, we go left to right through the array to build out both sequences. 
//every time we are considering the ith element in the array, we want to make sure that we maximize the maximum previous
//value of both our sequences. 

signed main() {
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
        int ans = 0;
        int pa = 1e9;
        int pb = 1e9;
        for(int i = 0; i < n; i++){
            if(pa >= a[i] && pb >= a[i]){
                if(pa < pb) {
                    pa = a[i];
                }
                else {
                    pb = a[i];
                }
            }
            else if(pa >= a[i]){
                pa = a[i];
            }
            else if(pb >= a[i]){
                pb = a[i];
            }
            else {
                ans ++;
                if(pa < pb) {
                    pa = a[i];
                }
                else {
                    pb = a[i];
                }
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
