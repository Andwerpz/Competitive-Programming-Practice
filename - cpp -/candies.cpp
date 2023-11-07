#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1810B

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<bool> bits(0);
        while(n != 0){
            bits.push_back(n % 2);
            n /= 2;
        }
        if(!bits[0]){
            cout << "-1\n";
            continue;
        }
        vector<int> ans(0);
        ans.push_back(2);
        for(int i = bits.size() - 2; i >= 1; i--){
            ans.push_back(1 + bits[i]);
        }
        cout << ans.size() << "\n";
        for(int i = 0; i < ans.size(); i++){
            cout << ans[i] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
