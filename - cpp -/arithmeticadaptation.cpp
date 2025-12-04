#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;

//NCPC 2025 - A

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int n; cin >> n;
    if (n == 1) {
        cout << "-1 2\n";
    } else if (n == -1) {
        cout << "-2 1\n";
    } else if (n == 0) {
        cout << "-1 1\n";
    } else {
        cout << n / 2 <<  " " << (n - n / 2) << '\n';
    }
    return 0;
}