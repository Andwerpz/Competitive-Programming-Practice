#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

vector<int> prime_sieve(int n) {
    vector<int> lp(n + 1);
    vector<int> pr;
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
    return pr;
}
