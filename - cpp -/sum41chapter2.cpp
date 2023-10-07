#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Meta Hacker Cup 2023 B2

//once we generate the prime factorization for p, we can reduce the number of elements by combining factors. 

//to find the minimum, we can just do brute force backtracking. 

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
    for(int i = 0; i < pr.size(); i++){
        while(val % pr[i] == 0){
            factors.push_back(pr[i]);
            val /= pr[i];
        }
    }
    if(val != 1){
        factors.push_back(val);
    }
    return factors;
}

void solve(vector<int> f, vector<int>& ans) {
    int sum = 0;
    for(int i = 0; i < f.size(); i++){
        sum += f[i];
    }
    if(sum > 41) {
        return;
    }
    //go to next states
    sort(f.begin(), f.end());
    set<pair<int, int>> used;
    for(int i = 0; i < f.size(); i++){
        for(int j = i + 1; j < f.size(); j++){
            if(used.find({f[i], f[j]}) != used.end()) {
                continue;
            }
            used.insert({f[i], f[j]});
            vector<int> next(0);
            for(int k = 0; k < f.size(); k++){
                if(k == i || k == j){
                    continue;
                }
                next.push_back(f[k]);
            }
            next.push_back(f[i] * f[j]);
            solve(next, ans);
        }
    }
    //try the current
    while(sum != 41) {
        f.push_back(1);
        sum ++;
    }
    if(ans.size() > f.size()) {
        ans = f;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    std::ifstream in("val.txt");
    std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
    std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
    
    std::ofstream out("val_out.txt");
    std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
    
    prime_sieve(1e5);
    int t;
    cin >> t;
    int caseno = 0;
    while(t--){
        caseno ++;
        cout << "Case #" << caseno << ": ";
        int p;
        cin >> p;
        vector<int> f = find_prime_factors(p);
        int sum = 0;
        for(int i = 0; i < f.size(); i++){
            sum += f[i];
        }
        if(sum > 41) {
            cout << "-1\n";
            continue;
        }
        vector<int> ans = f;
        while(sum != 41) {
            ans.push_back(1);
            sum ++;
        }
        solve(f, ans);
        cout << ans.size() << " ";
        for(int i = 0; i < ans.size(); i++){
            cout << ans[i] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
