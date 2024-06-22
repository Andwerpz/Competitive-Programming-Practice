#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 979D

//first,  k | gcd(x, v) tells us that x and v must both be multiples of k. 

//now, let's disregard the gcd and sum constraints, and focus on the xor constraint. Given some array, to maximize
//x xor a[i], we can keep a trie with all the values a[i] in the array, and greedily traverse the trie from the most
//significant bit to least. 

//To account for the sum constraint, we can keep for each trie node, the minimum array value in it's subtree. Then, 
//we can only traverse to that node for a given x if minv <= s - x. 

//Finally, to account for the gcd constraint, we can keep 10^5 tries. T[i] holds all the values in the array that are 
//divisible by i, and to answer some query x, k, s, we just need to query trie T[k].

//To handle type 1 queries, we just need to find all values d | u, and insert into T[d], u. 

struct Trie {
    struct TrieNode {
        TrieNode* c[2];
        int min_val;
    };

    TrieNode head;

    Trie() {
        this->head = TrieNode();
    }

    void insert(int a){
        TrieNode* ptr = &head;
        for(int i = 29; i >= 0; i--){
            bool bit = a & (1 << i);
            if(ptr->c[bit] == nullptr) {
                TrieNode* next = new TrieNode();
                next->min_val = a;
                ptr->c[bit] = next;
            }
            ptr = ptr->c[bit];
            ptr->min_val = min(ptr->min_val, a);
        }
    }

    int query(int x, int s) {
        TrieNode* ptr = &head;
        for(int i = 29; i >= 0; i--){
            bool bit = x & (1 << i);
            //preferred bit
            if(ptr->c[!bit] != nullptr && ptr->c[!bit]->min_val <= s - x) {
                ptr = ptr->c[!bit];
                continue;
            }
            //not preferred bit
            else if(ptr->c[bit] != nullptr && ptr->c[bit]->min_val <= s - x){
                ptr = ptr->c[bit];
                continue;
            }
            //rip
            return -1;
        }
        return ptr->min_val;
    }
};

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

vector<int> find_divisors(int val) {
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
    return div;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    prime_sieve(1e5 + 10);
    vector<Trie> t(1e5 + 10);
    int q;
    cin >> q;
    while(q--){
        int type;
        cin >> type;
        if(type == 1){
            int u;
            cin >> u;
            vector<int> d = find_divisors(u);
            for(int i = 0; i < d.size(); i++){
                t[d[i]].insert(u);
            }
        }
        else {
            int x, k, s;
            cin >> x >> k >> s;
            if(x % k != 0){
                cout << "-1\n";
            }
            else {
                cout << t[k].query(x, s) << "\n";
            }
        }
    }
    
    return 0;
}