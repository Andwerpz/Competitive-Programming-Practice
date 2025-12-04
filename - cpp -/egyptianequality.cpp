#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;

//NCPC 2025 - E

//if the parity of casing stones is odd, then it's always impossible

//otherwise, there are three cases:
// - the A component contains the top cell
// - the A component contains the leftmost cell
// - the A component contains the rightmost cell

//just have to write some code to generate traversal for each case such that at 
//any point in the traversal, there are exactly 2 components. 

void try_exp(vector<pair<int, int>>& ord, vector<string>& a, int n, int m, int cnt) {
    assert(cnt % 2 == 0);
    int ccnt = 0;
    int ansind = -1;
    for(int i = 0; i < ord.size(); i++) {
        int r = ord[i].first, c = ord[i].second;
        assert(a[r][c] == '.' || a[r][c] == 'C');
        if(a[r][c] == 'C') ccnt ++;
        if(cnt / 2 == ccnt) {
            ansind = i;
            break;
        }
    }
    if(ansind == -1) return;
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) {
        if(a[i][j] != '#') a[i][j] = 'B';
    }
    for(int i = 0; i < ord.size(); i++) {
        int r = ord[i].first, c = ord[i].second;
        assert(a[r][c] == 'B');
        if(i <= ansind) a[r][c] = 'A';
    }
    for(int i = 0; i < n; i++) {
        cout << a[i] << "\n";
    }
    exit(0);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int n;
    cin >> n;
    int m = n * 2 - 1;
    vector<string> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    int cnt = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(a[i][j] == 'C') cnt ++;
        }
    }
    if(cnt % 2 == 1) {
        cout << "impossible\n";
        return 0;
    }
    {
        vector<pair<int, int>> ord;
        int h = 1;
        for(int i = 0; i < 2 * (n - 1) - 1; i++) {
            for(int j = 0; j < h; j++) {
                ord.push_back({n - j - 1, i});
            }
            if(i < n - 2) h ++;
            else h --;
        }
        try_exp(ord, a, n, m, cnt);
    }
    {
        vector<pair<int, int>> ord;
        int h = 1;
        for(int i = 0; i < 2 * (n - 1) - 1; i++) {
            for(int j = 0; j < h; j++) {
                ord.push_back({n - j - 1, 2 * n - 2 - i});
            }
            if(i < n - 2) h ++;
            else h --;
        }
        try_exp(ord, a, n, m, cnt);
    }
    {
        vector<pair<int, int>> ord;
        for(int i = 0; i < n - 1; i++) {
            ord.push_back({i, n - 1});
            for(int j = 1; j <= i; j++) {
                ord.push_back({i, n - 1 + j});
                ord.push_back({i, n - 1 - j});
            }
        }
        try_exp(ord, a, n, m, cnt);
    }
    cout << "impossible\n";

    return 0;
}