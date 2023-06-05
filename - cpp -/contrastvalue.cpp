#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1832C

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<int> a(0);
        for(int i = 0; i < n; i++){
            int next;
            cin >> next;
            if(i == 0 || a[a.size() - 1] != next) {
                a.push_back(next);
                //cout << "PUSH BACK : " << next << "\n";
            }
        }
        //cout << n << "\n";
        n = a.size();
        if(n == 1){
            cout << "1\n";
            continue;
        }
        bool same = a[0] == a[n - 1];
        int ans = 2;
        for(int i = 1; i < n - 1; i++){
            //cout << "BOOL : " << (i < n - 1) << " " << i << " " << (n - 1) << "\n";
            same &= a[i] == a[0];
            if(a[i - 1] < a[i] && a[i] > a[i + 1]){
                ans ++;
            }
            else if(a[i - 1] > a[i] && a[i] < a[i + 1]){
                ans ++;
            }
        }
        if(same){
            ans -= 1;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
