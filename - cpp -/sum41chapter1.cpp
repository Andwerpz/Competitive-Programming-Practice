#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Meta Hacker Cup 2023 B1

//let's first find the prime factorization of p. The sum of the prime factorization is the lowest we can get, 
//so if the sum of the prime factors is greater than 41, it is impossible to represent p. 

//otherwise, if it is less than or equal to 41, we can just pad the remaining sum with 1s. 

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
        while(sum != 41) {
            f.push_back(1);
            sum ++;
        }
        cout << f.size() << " ";
        for(int i = 0; i < f.size(); i++){
            cout << f[i] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
