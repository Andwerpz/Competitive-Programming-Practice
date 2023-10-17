#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2010 J

void solve(int n) {
    int x, y; cin >> x >> y;

    if (x < y) swap(x, y);

    vector<vector<vector<int>>> possi(x+1, vector<vector<int>> (y+1));



    for (int i = 0; i < n; ++i) {
        int a; cin >> a;
        // cerr << "HEY" << endl;
        for (int j = 1; j <= a; ++j) {
            int wid = a / j;
            if (a % j == 0) {
                bool not_works = j > x || wid > y;
                if (not_works) continue;
                if (j < a/j) continue;
                possi.at(j).at(a/j).push_back(1 << i);
            }
        }
    }

    // cerr << "hey" << endl;

    for (int i = 1; i <= x; ++i) {
        for (int j = 1; j <= min(y, i); ++j) {
            // if (possi[i][j].size()) {
            //     cerr << "i : " << i << " j : " << j << endl;
            // }
            for (auto k : possi[i][j]) {
                
                for (int l = 1; l + i <= x; ++l) {
                    for (auto m : possi[max(l, j)][min(l, j)]) {
                        if ((m & k) == 0) {
                            // cerr << "COMB" << endl;
                            possi[max(i+l, j)][min(j, i+l)].push_back(m ^ k);
                        }
                    }
                }

                for (int l = 1; l + j <= y; ++l) {
                    for (auto m : possi[max(i, l)][min(i, l)]) {
                        if ((m & k) == 0) {
                            // cerr << "COMB2" << endl;
                            possi[max(i, j+l)][min(j+l, i)].push_back(m ^ k);
                        }
                    }
                }
            }
        }
    }


    bool works = false;

    for (auto k : possi[x][y]) {
        if (k == (1 << n) - 1) {
            works = true;
        }
    }

    if (works) cout << "Yes\n";
    else cout << "No\n";

}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    int caseno = 0;
    while(n != 0){
        caseno ++;
        cout << "Case " << caseno << ": ";
        solve(n);
        cin >> n;
    }
    
    return 0;
}
