#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<int, int>;

//2023 Columbia University Local Contest C

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string s; cin >> s;
    int n = s.size();

    int c_cnt = 0;

    for (auto c : s) {
        if (c == 'c') {
            c_cnt++;
        }
    }


    vector<int> ans;
    int no_c = 0;
    for (int i = n-1; i > -1 && c_cnt; --i) {
        if (s[i] != 'c') {
            ans.push_back(i);
            c_cnt--;
            no_c++;
        } else {
            c_cnt--;
        }
    }


    // cerr << "no_c : " << no_c << endl;

    reverse(ans.begin(), ans.end());


    vector<int> ans2;
    for (int i = 0; i < n && no_c; ++i) {
        if (s[i] == 'c') {
            ans2.push_back(i);
            no_c--;
        }
    }


    for (auto x : ans) ans2.push_back(x);

    if (!ans2.size()) {
        cout << 1 << endl;
        cout << 1 << endl;
        return 0;
    }

    cout << ans2.size() << endl;
    for (auto x : ans2) {
        cout << x+1 << " ";
    }
    cout << endl;


    return 0;
}