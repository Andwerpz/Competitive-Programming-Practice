#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 816B

//just use prefix sums to simulate range modification, and then use another prefix sum
//to answer range queries for how many temperatures have at least k recommendations. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k, q;
    cin >> n >> k >> q;
    vector<int> t(300000);
    for(int i = 0; i < n; i++){
        int l, r;
        cin >> l >> r;
        t[l] += 1;
        t[r + 1] += -1;
    }
    vector<int> pfx(300000);
    for(int i = 1; i < t.size(); i++){
        t[i] += t[i - 1];
        if(t[i] >= k){
            pfx[i] = 1;
        }
    }
    cout << endl;
    for(int i = 1; i < pfx.size(); i++){
        pfx[i] += pfx[i - 1];
    }
    for(int i = 0; i < q; i++){
        int a, b;
        cin >> a >> b;
        cout << (pfx[b] - pfx[a - 1]) << endl;
    }
    
    return 0;
}
