#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 13 G

//the maximum amount of factors is just going to be the amount of factors in the prime factorization of the number. 

//since we are only given one number up to 10^9, we can just calculate the prime factorization of the number. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    const int N = sqrt(1e9) + 100; //generate all primes up to this value
    vector<int> lp(N + 1);  //largest prime factor
    vector<int> pr; //prime list

    for(int i = 2; i <= N; i++) {
        if(lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
        }
        for(int j = 0; i * pr[j] <= N; j++) {
            lp[i * pr[j]] = pr[j];
            if (pr[j] == lp[i]) {
                break;
            }
        }
    }

    int ans = 0;
    int x;
    cin >> x;
    for(int i = 0; i < pr.size(); i++){
        while(x % pr[i] == 0){
            x /= pr[i];
            ans ++;
        }
    }
    if(x != 1){
        ans ++;
    }
    cout << ans << "\n";
    
    return 0;
}
