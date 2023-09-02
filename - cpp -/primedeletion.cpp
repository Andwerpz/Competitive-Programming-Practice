#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1861A

//i think that it's always the case that we can find a prime of length 2 in the sequence. 
//i didn't prove it, but it worked. 

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    prime_sieve(100);
    int t;
    cin >> t;
    set<int> pset;
    for(int i = 0; i < pr.size(); i++){
        pset.insert(pr[i]);
    }
    while(t--) {
        string s;
        cin >> s;
        int ans = -1;
        for(int i = 0; i < s.size(); i++){
            for(int j = i + 1; j < s.size(); j++){
                int next = (s[i] - '0') * 10 + (s[j] - '0');
                if(pset.find(next) != pset.end()) {
                    ans = next;
                }
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
