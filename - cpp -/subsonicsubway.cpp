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

//Meta Hacker Cup 2024 Round 1 - A

//just compute the maximum time / miles allowed by any delivery, and then check if that works for all deliveries.

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    ifstream in("--in--.txt");
    streambuf *cinbuf = cin.rdbuf(); //save old buf
    cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
    
    ofstream out("--out--.txt");
    streambuf *coutbuf = cout.rdbuf(); //save old buf
    cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
    
    ld epsilon = 1e-12;
    int t;
    cin >> t;
    int casi = 0;
    while(t--){
        casi ++;
        int n;
        cin >> n;
        vector<pair<ld, ld>> a(n);
        ld mx_tpm = 1e18;
        for(int i = 0; i < n; i++){
            cin >> a[i].first >> a[i].second;
            mx_tpm = min(mx_tpm, a[i].second / (i + 1));
        }
        bool is_valid = true;
        for(int i = 0; i < n; i++){
            ld cur = (i + 1) * mx_tpm;
            if(cur + epsilon < a[i].first || cur - epsilon > a[i].second) {
                is_valid = false;
            }
        }
        cout << "Case #" << casi << ": ";
        if(!is_valid){
            cout << "-1\n";
        }
        else {
            cout << fixed << setprecision(10) << (1.0 / mx_tpm) << "\n";
        }
    }
    
    return 0;
}