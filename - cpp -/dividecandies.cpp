
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1056B

//use remainders to solve this problem. 

//lets say for each number i from 1 - n, we can find the value of (i ^ 2) % m. Using this information, we can easily compute how many valid cells there are.
//obviously the cells with two remainder 0 numbers are compatible, but also cells with remainder 1 and m - 1, 2 and m - 2, and so on. If we compute how many
//of each remainder there are, we can just add to the ans, num 1 * num m - 1 and so on. 

//to compute the amount, we can use the observation that if a number has the same remainder as another number before squaring, it'll have the remainder after squaring too.

//for numbers smaller than m, we can see that this is obvious, since for each remainder there is only 1 number smaller than m. 
//for numbers larger than m, we can easily prove this. Each number falls into the form a * m + b, where b is the remainder. When squared, you'll get 
//(a * m) ^ 2 + 2(a * m * b) + b ^ 2. Observe that the value of a doesn't matter in computing the final remainder, only the value of b^2 will matter to the remainder
//and so only the value b will matter.

using namespace std;

int main() {

    ll n, m;
    cin >> n >> m;
    vector<ll> rem(m);
    vector<ll> temp(m);
    if(n >= m){
        n -= m - 1;
        ll multiple = n / m;
        ll remainder = n % m;
        for(int i = 0; i < temp.size(); i++){
            if(i != 0){
                temp[i] ++;
            }
            temp[i] += multiple;
            if(i < remainder){
                temp[i] ++;
            }
        }
    }
    else{
        for(int i = 1; i <= n; i++){
            temp[i] ++;
        }
    }
    for(int i = 0; i < temp.size(); i++){
        ll next = i * i;
        next %= m;
        rem[next] += temp[i];
    }
    ll ans = rem[0] * rem[0];
    for(int i = 1; i < rem.size(); i++){
        ans += rem[i] * rem[rem.size() - i];
    }
    cout << ans << endl;

    return 0;
}



