#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1575A

//implementation problem. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<pair<string, int>> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i].first;
        a[i].second = i;
    }
    sort(a.begin(), a.end(), [](pair<string, int>& _a, pair<string, int>& _b) {
        string a = _a.first;
        string b = _b.first;
        for(int i = 0; i < a.size(); i++){
            if(a[i] == b[i]){
                continue;
            }
            if(i % 2 == 0){
                return a[i] < b[i];
            }
            else {
                return a[i] > b[i];
            }
        }
        return true;
    });
    for(int i = 0; i < n; i++){
        cout << a[i].second + 1 << " ";
    }
    cout << "\n";
    
    return 0;
}