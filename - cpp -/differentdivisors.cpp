
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1474B

//a number that has 4 divisors. 1 divisor is going to be itself, and another one is going to be 1. If you want to make the smallest number, 
//then the other two divisors must be prime, and they must be as small as possible. Greedily find the 2 smallest prime numbers that 
//are greater than d, and are separated by at least d. Multiply them, and that's your answer

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //precompute list of primes
    vector<bool> isPrime = vector<bool>(100005, true);
    vector<int> primes = vector<int>();
    for(int i = 2; i < isPrime.size(); i++){
        if(isPrime[i]){
            for(int j = i * 2; j < isPrime.size(); j += i){
                isPrime[j] = false;
            }
        }
    }
    for(int i = 2; i < isPrime.size(); i++){
        if(isPrime[i]){
            primes.push_back(i);
        }
    }

    int t;
    cin >> t;
    while(t-- > 0){
        int d;
        cin >> d;
        ll a = -1;
        ll b = -1;
        ll high = primes.size() - 1;
        ll low = 0;
        ll mid = low + (high - low) / 2;
        while(low <= high){
            if(primes[mid] >= 1 + d){
                if(a == -1 || a > primes[mid]){
                    a = primes[mid];
                }
                high = mid - 1;
            }
            else {
                low = mid + 1;
            }
            mid = low + (high - low) / 2;
        }
        high = primes.size() - 1;
        low = 0;
        mid = low + (high - low) / 2;
        while(low <= high){
            if(primes[mid] >= a + d){
                if(b == -1 || b > primes[mid]){
                    b = primes[mid];
                }
                high = mid - 1;
            }
            else {
                low = mid + 1;
            }
            mid = low + (high - low) / 2;
        }
        cout << ((ll)a * (ll)b) << endl;
    }

    return 0;
}



