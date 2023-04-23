#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 13 C

//you can just brute force calculate all prime factorizations. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    const int N = sqrt(1e9) + 10; //generate all primes up to this value
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

    int n;
    cin >> n;
    while(n != 4){
        int cnt = 0;
        int sum = 0;
        while(true) {
            cnt ++;
            if(n < lp.size() && lp[n] == n){
                break;
            }
            int tmp = n;
            for(int i = 0; i < pr.size(); i++){
                while(tmp % pr[i] == 0){
                    sum += pr[i];
                    tmp /= pr[i];
                    //cout << "FACTOR : " << pr[i] << "\n";
                }
            }
            if(sum == 0){
                break;
            }
            //cout << "TMP : " << tmp << "\n";
            if(tmp != 1){
                sum += tmp;
            }
            n = sum;
            sum = 0;
            //cout << "NEW N : " << n << "\n";
        }
        cout << n << " " << cnt << "\n";
        cin >> n;
    }
    
    return 0;
}
