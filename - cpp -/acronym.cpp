#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<bool> vb;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

//2024 ICPC Polish Collegiate Programming Contest - A

//implementation

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n;
    cin >> n;
    vector<string> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    vb v(26, false);
    vi vind(26, -1);
    for(int i = 0; i < n; i++){
        v[a[i][0] - 'A'] = true;
        vind[a[i][0] - 'A'] = i;
    }
    bool is_valid = false;
    for(int i = 0; i < n; i++){
        // cout << "I : " << i << endl;
        bool cur_valid = true;
        for(int j = 0; j < a[i].size(); j++){
            // cout << "J : " << j << " " << a[i][j] - 'A' << endl;
            if(!v[a[i][j] - 'A']) cur_valid = false;
        }
        if(cur_valid) {
            cout << a[i].size() << "\n";
            for(int j = 0; j < a[i].size(); j++){
                cout << a[vind[a[i][j] - 'A']] << " ";
            }
            cout << "\n";
            is_valid = true;
            break;
        }
    }
    if(!is_valid) cout << "-1\n";

    return 0;
}