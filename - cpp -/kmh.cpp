#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;

//NCPC 2025 - K

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int n; cin >> n;
    int mx = 0;
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        if(s == "/") {
            cout << mx << '\n';
        } else {
            cout << s << '\n';
            int num = stoi(s);
            if(num % 10 == 0) mx = max(mx, num + 10);
            else mx = max(mx, num / 10 * 10 + 10);
        }
    }

    return 0;
}