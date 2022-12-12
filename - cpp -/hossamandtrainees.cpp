#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces 1771C

//the goal is to find if the gcd between any pair of numbers is greater than 1. If yes, then print "YES". 

//if we generate the prime factorization for every number, and two numbers share a prime factor, then
//we know that the gcd between those two numbers is not equal to 1. 

//to do this, we can just generate all primes from 2 to sqrt(10^9), which there are around 3500 of. 
//note that if a number less than 10^9 has a prime factor greater than sqrt(10^9), then it can only have 1 of them. 
//so if we divide the number by all primes under sqrt(10^9), and the number is still not 1, then it is a prime

//there is another way to solve this problem using better prime factorization algorithms where you can just factor each number 
//normally. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //generate prime factorization of all numbers from 0 - N.
    int N = (int) sqrt(1e9) + 1; 
    vector<int> lpf(N + 1); //lowest prime factor
    vector<int> p;  //prime list
    for(int i = 2; i <= N; i++) {
        if(lpf[i] == 0) {
            lpf[i] = i;
            p.push_back(i);
        }
        for(int j = 0; i * p[j] <= N; j++) {
            lpf[i * p[j]] = p[j];
            if(p[j] == lpf[i]) {
                break;
            }
        }
    }
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        set<int> s;
        bool isValid = false;
        for(int i = 0; i < n; i++){
            int next;
            cin >> next;
            vector<int> f;
            for(int j : p) {
                if(next % j == 0){
                    f.push_back(j);
                }
                while(next % j == 0){
                    next /= j;
                }
            }
            if(next != 1){
                f.push_back(next);
            }
            for(int j : f){
                if(s.find(j) != s.end()){
                    isValid = true;
                }
                s.insert(j);
            }
        }
        cout << (isValid? "YES" : "NO") << "\n";
    }
    
    return 0;
}
