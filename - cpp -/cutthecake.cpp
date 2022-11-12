#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const ld pi = 3.141592653589;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    ld r;
    cin >> n >> k >> r;
    vector<ld> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    vector<ld> s(0);
    for(int i = 0; i < n; i++){
        ld deg = a[(i + 1) % n] - a[i];
        if(i == n - 1){
            deg += 180.0;
        }
        ld area = pi * (deg / 360.0) * r * r;
        s.push_back(area);
    }
    ld lSum = 0;
    ld rSum = 0;
    for(int i = 0; i < k; i++){
        rSum += s[i % s.size()];
    }
    ld ans = 0;
    for(int i = 0; i < s.size() * 3; i++){
        ans = max(ans, rSum - lSum);
        lSum += s[i % s.size()];
        rSum += s[(i + k) % s.size()];
    }
    cout.precision(17);
    cout << ans << fixed << "\n";
    
    return 0;
}
