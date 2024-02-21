#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//2018 South Central USA Regional - I

//for each die, find the orientation that minimizes the lexicographic ordering of it's faces. 

//then, just match similar dice. 

vector<int> r0(vector<int> a){
    swap(a[0], a[2]);
    swap(a[1], a[3]);
    swap(a[2], a[3]);
    return a;
}

vector<int> r1(vector<int> a){
    swap(a[0], a[4]);
    swap(a[1], a[5]);
    swap(a[4], a[5]);
    return a;
}

vector<int> r2(vector<int> a){
    swap(a[2], a[4]);
    swap(a[3], a[5]);
    swap(a[4], a[5]);
    return a;
}

void permute(vector<int> a, set<vector<int>>& m) {
    if(m.count(a)) {
        return;
    }
    m.insert(a);
    permute(r0(a), m);
    permute(r1(a), m);
    permute(r2(a), m);
}

vector<vector<int>> gen_key(vector<int> a) {
    set<vector<int>> m;
    permute(a, m);
    vector<vector<int>> key;
    for(auto i = m.begin(); i != m.end(); i++){
        key.push_back(*i);
    }
    return key;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(6));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 6; j++){
            cin >> a[i][j];
        }
    }
    map<vector<vector<int>>, int> m;
    for(int i = 0; i < n; i++){
        m[gen_key(a[i])] ++;
    }
    int ans = 0;
    for(auto i = m.begin(); i != m.end(); i++){
        ans = max(ans, i -> second);
    }
    cout << ans << "\n";
    
    return 0;
}
