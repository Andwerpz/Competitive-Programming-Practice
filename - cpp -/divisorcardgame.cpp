#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <cassert>
#include <cstring>
typedef long long ll;
typedef long double ld;
using namespace std;
typedef vector<int> vi;
typedef vector<ll> vl;

//ICPC Asia Taichung Regional 2025 - D

//cool EV problem

//what's the probability for person j to get card i?
//if person j was dealt card i, then it's 1
//otherwise, it may not be 1

//in order for person j to get card i, j must get cards c_1, c_2, ..., c_n where c_n = a_i 
// c_i > c_{i + 1}
// and c_1 is dealt initially to player j
// and c_i is played in order to win card c_{i + 1}

//what is the probability of some chain?
//let p_i be the set of cards such that for each x in p_i, c_{i - 1} < x <= c_i and c_i | x
//then, the probability of such a chain is
// \prod_{k = 1}^{n} \frac{1}{\sum_{j = k}^{n} |p_j|}

//how to derive this:
//first observe that p_i and p_j are disjoint for i != j. 
//so the only requirement for the chain to work is that c_i appears before all other elements in p_i,
//and that c_i appears before all c_j where i < j
//c_1 is already owned, so we can effectively ignore it
//c_2 must appear first relative to everything else, so this happens with probability 
// \frac{1}{\sum_{i = 2}^{n} |p_i|}
//given that this happens, c_3 must appear first relative to everything except for elements in p_1, 
//so this happens with probability
// \frac{1}{\sum_{i = 3}^{n} |p_i|}
//these are independent since we didn't put any restrictions on the ordering of elements in 
//p_3 \cup p_4 \cdots p_n, it's just that they have to all be after c_2
//if we keep going, we get the above formula. 

//finally, how to use this to solve?
//observe that if we initially own some card, if we can find the probability sum of all paths starting
//from that card, then that is that cards 'contribution' to that player. So taking the sum over all
//cards that player was initially dealt will give us the expected amount of cards that player will get.

//dp[i][j] = sum of probabilities with chain
// starting at card i
// having j 'relevant' cards

//number of relevant cards just means |p_1 \cup p_2 \cdots \cup p_n| so far in the chain. 
//this is so we can compute transition probabilities quickly
//a transition will look like
//dp[k][j + p] += dp[i][j] * (1 / (j + p))
//where k < i and a[k] % a[i] == 0

//note that there are some special cases you have to worry about regarding already dealt cards. 
//an already dealt card cannot be in the middle of a chain, so if you see one you have to stop
//also, a chain cannot start from an already dealt card, so states such that b[i] != -1 cannot 
//have outgoing transitions. 

const ll mod = 998244353;

ll pow(ll a, ll b) {
    ll res = 1, p = a;
    while(b != 0) {
        if(b % 2) res = (res * p) % mod;
        p = (p * p) % mod;
        b /= 2;
    }
    return res;
}

ll inv(ll a) {
    return pow(a, mod - 2);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vl a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    reverse(a.begin(), a.end());
    vl b(n);
    for(int i = 0; i < n; i++) {
        cin >> b[i];
        b[i] --;
    }
    reverse(b.begin(), b.end());
    //U[i] = probability of card i being discarded
    // this is either 0 or 1
    vl U(n, 1);    
    for(int i = 0; i < n; i++) {
        if(b[i] != -1) {
            U[i] = 0;
        }
        else {
            for(int j = i - 1; j >= 0; j--) { 
                if((a[j] % a[i]) == 0 && U[j] == 0) U[i] = 0;
            }
        }
    }
    vl inva(n + 1);
    for(int i = 1; i <= n; i++) inva[i] = inv(i);
    //dp[i][j] = sum of probabilities with a chain
    // starting at card i
    // has j 'relevant' cards
    vector<vl> dp(n, vl(n + 1, 0));
    //base cases
    for(int i = 0; i < n; i++) if(!U[i]) dp[i][0] = 1;
    for(int i = n - 1; i >= 0; i--) {
        if(U[i]) continue;
        if(b[i] != -1) continue;
        for(int j = 0; j <= n; j++) {
            if(dp[i][j] == 0) continue;
            int p = 1;
            for(int k = i - 1; k >= 0; k--) {
                if(a[k] % a[i] != 0) continue;
                if(U[k]) continue;
                assert(j + p <= n);
                dp[k][j + p] = (dp[k][j + p] + dp[i][j] * inva[j + p]) % mod;
                if(b[k] != -1) break;
                p ++;
            }
        }
    }
    vl ans(m, 0);
    for(int i = 0; i < n; i++) {
        ll sum = 0;
        for(int j = 0; j <= n; j++) sum = (sum + dp[i][j]) % mod;
        if(b[i] != -1) ans[b[i]] = (ans[b[i]] + sum) % mod;
    }
    for(int i = 0; i < m; i++) cout << ans[i] << " ";
    cout << "\n";

    return 0;
}