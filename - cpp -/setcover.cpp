#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
// typedef __int128 lll;
// typedef __float128 lld;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ifstream in("--in--.txt");
    streambuf *cinbuf = cin.rdbuf(); //save old buf
    cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
    
    ofstream out("--out--.txt");
    streambuf *coutbuf = cout.rdbuf(); //save old buf
    cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

    int t;
    cin >> t;
    int casi = 0;
    while(t--){
        int n, k;
        cin >> n >> k;
        int nro = 0, nrq = 0;
        vector<string> g(n);
        for(int i = 0; i < n; i++){
            cin >> g[i];
        }
        int ans = -1;
        if(k >= 4){
            int minr = 1e9;
            int minc = 1e9;
            int maxr = -1;
            int maxc = -1;
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    if(g[i][j] != '0'){
                        minr = min(minr, i);
                        minc = min(minc, j);
                        maxr = max(maxr, i);
                        maxc = max(maxc, j);
                    }
                }
            }
            ans = (maxr - minr + 1) * (maxc - minc + 1);
        }
        else {
            //k <= 3

        }
        // vvi pfxo(n + 1, vi(n + 1, 0)), pfxq(n + 1, vi(n + 1, 0));
        // for(int i = 1; i <= n; i++){
        //     for(int j = 1; j <= n; j++){
        //         pfxo[i][j] = pfxo[i - 1][j] + pfxo[i][j - 1] - pfxo[i - 1][j - 1] + (g[i - 1][j - 1] == '1');
        //         pfxq[i][j] = pfxq[i - 1][j] + pfxq[i][j - 1] - pfxq[i - 1][j - 1] + (g[i - 1][j - 1] == '?');
        //     }
        // }

        cout << "Case #" << casi << ": " << ans << "\n";
    }
    
    return 0;
}