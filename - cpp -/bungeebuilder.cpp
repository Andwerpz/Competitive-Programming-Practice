#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 09 B

//monotonic stack. 

//for the ith mountain, try to make the maximum height bungee cord the left. Then, use min segtree to find the maximum jump height from the cord. 

const int N = 2e6;  //limit for segtree size
int n;
int t[2 * N];

void modify(int p, int value) { // set value at position p
    p += n;
    t[p] = value;
    for (p /= 2; p > 0; p /= 2) {
        t[p] = min(t[p * 2], t[p * 2 + 1]);
    }
}

int query(int l, int r) { // min on interval [l, r)
    int res = t[l + n];
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
        if (l % 2 == 1) {
            res = min(res, t[l]);
            l++;
        }
        if (r % 2 == 1) {
            r--;
            res = min(res, t[r]);
        }
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
        modify(i, a[i]);
    }
    int ans = 0;
    stack<pair<int, int>> s;
    for(int i = 0; i < n; i++){
        while(s.size() != 0 && s.top().first < a[i]) {
            s.pop();
        }
        if(s.size() != 0){
            int ind = s.top().second;
            ans = max(ans, a[i] - query(ind, i));
        }
        s.push({a[i], i});
    }    
    s = stack<pair<int, int>>();
    for(int i = n - 1; i >= 0; i--){
        while(s.size() != 0 && s.top().first < a[i]) {
            s.pop();
        }
        if(s.size() != 0){
            int ind = s.top().second;
            ans = max(ans, a[i] - query(i, ind + 1));
        }
        s.push({a[i], i});
    }
    cout << ans << "\n";

    return 0;
}
