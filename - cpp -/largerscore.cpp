#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//AtCoder - ARC138A

//we just want to replace one of the values in the k prefix with some other larger value that is initially
//outside of the kth prefix. 

//for each value that is outside of the kth prefix, we want to find the value that is inside of the kth prefix
//that is less than it, and closest to it. 

void insert(map<int, int>& m, int val, int index) {
    if(m.find(val) == m.end()) {
        m.insert({val, index});
    }
    m[val] = index;
    auto ptr = m.upper_bound(val);
    while(ptr != m.end()) {
        m.erase(ptr ++);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    map<int, int> m;    //increasing value -> increasing index
    for(int i = 0; i < n; i++){
        cin >> a[i];
        if(i < k) {
            insert(m, a[i], i);
        }
    }
    int ans = 1e9;
    for(int i = k; i < n; i++){
        if(a[i] <= m.begin() -> first) {
            continue;
        }
        auto ptr = m.lower_bound(a[i]);
        ptr --;
        int n_ans = abs(i - ptr->second);
        ans = min(ans, n_ans);
    }
    if(ans == 1e9) {
        ans = -1;
    }
    cout << ans << "\n";
    
    return 0;
}
