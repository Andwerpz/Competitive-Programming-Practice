#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1836A

//you just have to make sure the count of robots reporting x robots in front is less than or equal to the
//number of robots reporting x - 1 robots for all x >= 1. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> cnt(100, 0);
        for(int i = 0; i < n; i++){
            int next;
            cin >> next;
            cnt[next] ++;
        }
        bool ans = true;
        for(int i = 1; i < cnt.size(); i++){
            ans &= cnt[i] <= cnt[i - 1];
        }
        cout << (ans? "YES\n" : "NO\n");
    }
    
    return 0;
}
