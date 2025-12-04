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

//Meta Hacker Cup 2025 Round 1 - A

//fix player 1 to win

//first, p1 must get at least m points
//then, if p2 can be assigned points x such that x <= m - 2, this works. 
//otherwise, we must go over the threshold. This involves parity. 

bool solve(int n, int m) {
    //not enough points?
    if(n < m) {
        return 0;
    }
    //p1 gets m points
    n -= m;
    if(n <= m - 2) {
        return 1;
    }
    //else, this is parity
    return (n % 2) == (m % 2);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ifstream in("deciding_points_input.txt");
    streambuf *cinbuf = cin.rdbuf(); //save old buf
    cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
    
    ofstream out("--out--.txt");
    streambuf *coutbuf = cout.rdbuf(); //save old buf
    cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

    int t;
    cin >> t;
    int casi = 0;
    while(t--) {
        casi ++;
        ll n, m;
        cin >> n >> m;
        bool ans = solve(n, m);
        cout << "Case #" << casi << ": " << (ans? "YES" : "NO") << "\n";
    }
    
    return 0;
}