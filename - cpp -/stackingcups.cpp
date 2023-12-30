#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Rocky Mountain Regional 2016 I

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<pair<int,string>> cups;

    for(int i = 0; i < n; i++) {
        string one, two; cin >> one >> two;
        if(one[0] >= 'a') {
            cups.push_back({stoi(two),one});
        } else {
            cups.push_back({stoi(one)/2, two});
        }
    }
    sort(cups.begin(),cups.end());

    for(auto c : cups) cout << c.second << '\n';
    
    return 0;
}
