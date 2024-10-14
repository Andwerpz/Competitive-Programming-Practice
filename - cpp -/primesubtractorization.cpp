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

//Meta Hacker Cup 2024 Round 1 - B

//note that subtracting two odds will always yield an even, so any prime represented by the difference
//between two primes must be betwee 2 and some prime, except for 2, which can be represented by 5 - 3. 

//Therefore, just have to count the number of adjacent primes less than n. 

int N = 1e7 + 100;
vector<ll> lp(N + 1); //lowest prime factor 
vector<ll> pr(0); //prime list

void prime_sieve() {
    for(ll i = 2; i <= N; i++) {
        if(lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
        }
        for (ll j = 0; i * pr[j] <= N; j++) {
            lp[i * pr[j]] = pr[j];
            if (pr[j] == lp[i]) {
                break;
            }
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ifstream in("--in--.txt");
    streambuf *cinbuf = cin.rdbuf(); //save old buf
    cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
    
    ofstream out("--out--.txt");
    streambuf *coutbuf = cout.rdbuf(); //save old buf
    cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

    prime_sieve();
    set<int> s;
    for(int i = 0; i < pr.size(); i++){
        s.insert(pr[i]);
    }
    int t;
    cin >> t;
    int casi = 0;
    while(t--){
        casi ++;
        int n;
        cin >> n;
        int ans = 0;
        if(n >= 5){
            ans ++;
        }
        for(int i = 0; i <= pr.size(); i++){
            if(pr[i] + 2 == pr[i + 1] && pr[i + 1] <= n){
                ans ++;
            }
        }
        cout << "Case #" << + casi << ": " << ans << endl;
    }
    
    return 0;
}