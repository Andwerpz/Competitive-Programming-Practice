#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef std::pair<int, int> pii;
typedef std::pair<ll, ll> pll;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1981D

//first, notice that it's optimal for all a[i] to be prime. 
//two pairs of prime numbers will multiply to different things if the two unordered pairs are different. 

//given some amount of unique prime numbers that we can pull from, what's the largest array we can make
//before duplicating an unordered pair?

//First, treat each unique prime number as a node in a complete graph. Next, we can notice that any array
//is equivalent to a path through the graph where we only use each edge at most once. So, if we have n 
//primes, then the maximum array size is the maximum path length through a complete graph with n nodes 
//+ 1 (since we're counting nodes not edges). 

//Finding the maximum path length is not too hard, i used a very constructive method in my implementation, 
//but the editorial has a nicer euler path way of doing it. Once you found the maximum path, constructing the
//array is pretty easy. 

//Now to answer each test case, we can binary search for the minimum sz where sz primes can create an array
//of size >= n. 

vector<int> lp; //lowest prime factor 
vector<int> pr; //prime list

void prime_sieve(int n) {
    lp = vector<int>(n + 1);
    pr = vector<int>(0);
    for(int i = 2; i <= n; i++) {
        if(lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
        }
        for (int j = 0; i * pr[j] <= n; j++) {
            lp[i * pr[j]] = pr[j];
            if (pr[j] == lp[i]) {
                break;
            }
        }
    }
}

vector<int> find_prime_factors(int val) {
    vector<int> factors(0);
    while(val != 1) {
        factors.push_back(lp[val]);
        val /= lp[val];
    }
    return factors;
}

void find_divisors_helper(vector<int>& p, vector<int>& c, int ind, int val, vector<int>& ans) {
    if(ind == p.size()) {
        ans.push_back(val);
        return;
    }
    find_divisors_helper(p, c, ind + 1, val, ans);
    for(int i = 0; i < c[ind]; i++){
        val *= p[ind];
        find_divisors_helper(p, c, ind + 1, val, ans);
    }
}

//includes 1
vector<int> find_divisors(int val, bool include_one = true) {
    vector<int> factors = find_prime_factors(val);
    map<int, int> m;
    vector<int> p(0);
    vector<int> c(0);
    for(int i = 0; i < factors.size(); i++){
        int next = factors[i];
        if(m.find(next) == m.end()) {
            p.push_back(next);
            c.push_back(0);
            m.insert({next, m.size()});
        }
        int ind = m[next];
        c[ind] ++;
    }
    vector<int> div(0);
    find_divisors_helper(p, c, 0, 1, div);
    if(!include_one) {
        div.erase(div.begin());
    }
    return div;
}

vector<int> amts(2e3);
vector<vector<int>> d(2e3);
vector<int> gen_ans(int sz) {
    vector<int> ans(0);
    for(int i = 0; i < sz; i++){
        ans.push_back(pr[i]);
        ans.push_back(pr[i]);
        for(int j = 2; j < sz; j++){
            if(j * 2 >= sz) {
                continue;
            }
            if(i >= gcd(j, sz)) {
                continue;
            }
            for(int k = i + j; k != i; k = (k + j) % sz) {
                ans.push_back(pr[k]);
            }
            ans.push_back(pr[i]);
        }
    }
    ans.push_back(pr[0]);
    if(sz % 2 == 0){
        ans.push_back(pr[sz / 2]);
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    prime_sieve(1e6);
    //precompute for any amount, what's the maximum n it can handle. 
    for(int i = 1; i < amts.size(); i++){
        d[i] = find_divisors(i, false);
        sort(d[i].begin(), d[i].end());
        amts[i] = i * (i - 1) / 2 + i;
        if(i % 2 == 0){
            amts[i] -= i / 2 - 1;
        }
        amts[i] ++;
    }
    vector<vector<int>> ans(2e3, vector<int>(0));
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        int low = 1;
        int high = 2e3 - 1;
        int ind = high;
        while(low <= high) {
            int mid = low + (high - low) / 2;
            if(amts[mid] >= n) {
                ind = min(ind, mid);
                high = mid - 1;
            }
            else {
                low = mid + 1;
            }
        }
        if(ans[ind].size() == 0){
            ans[ind] = gen_ans(ind);
        }
        for(int i = 0; i < n; i++){
            cout << ans[ind][i] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}