#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 903B

//just have to heal enough so that you can attack until it's dead. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int h1, a1, c1;
    cin >> h1 >> a1 >> c1;
    int h2, a2;
    cin >> h2 >> a2;
    c1 -= a2;
    int nr_hit = (h2 + a1 - 1) / a1 - 1;
    int req_h = nr_hit * a2 + 1;
    vector<string> ans;
    while(req_h > h1) {
        h1 += c1;
        ans.push_back("HEAL");
    }
    while(h2 > 0){
        h2 -= a1;
        ans.push_back("STRIKE");
    }
    cout << ans.size() << "\n";
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i] << "\n";
    }
    
    return 0;
}