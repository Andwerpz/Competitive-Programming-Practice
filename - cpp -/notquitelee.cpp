
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//Codeforces - 1610D

//using a rule that "I" found, we can easily compute the amount of good subsequences.
//thx rowechen

//first, notice that any subsequence that contains an odd number is good. So from now on, we only consider subsequences with only even numbers.

//define nu(x) to be the maximum number of times we can divide x by 2. 
//in our subarray, if we take the nu of each value, it is good if and only if the minimum nu appears an even amount of times.

vector<ll> factorial(1000000);
vector<ll> pow2(1000000);
ll mod = pow(10, 9) + 7;

//n! / (r! * (n - r)!)
ll getComb(ll n, ll r){
    if(n == r){
        return 1;
    }
    //cout << "IN " << factorial[(int) n] << endl;
    ll ans = factorial[(int) n] / (factorial[(int) r] * factorial[(int) (n - r)]);  //can't mod factorial values
    ans %= mod;
    //cout << ans << endl;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    factorial[1] = 1;
    for(int i = 2; i < factorial.size(); i++){
        factorial[i] = factorial[i - 1] * i;
        factorial[i] %= mod;
    }
    pow2[0] = 1;
    for(int i = 1; i < pow2.size(); i++){
        pow2[i] = pow2[i - 1] * 2;
        pow2[i] %= mod;
    }
    //cout << mod << endl;
    //cout << "TEST: " << (pow2[(int) 200000] - 1) << endl;

    int n;
    cin >> n;
    vector<int> nums(n);
    for(int i = 0; i < n; i++){
        cin >> nums[i];
    }
    vector<ll> powers(100);
    for(int i = 0; i < n; i++){
        int next = nums[i];
        ll power = 0;
        while(next % 2 == 0){
            power ++;
            next /= 2;
        }
        powers[power] ++;
        //cout << nums[i] << " : " << power << endl;
    }
    //cout << endl;
    ll ans = (pow2[(int) powers[0]] - 1) * pow2[(int) (n - powers[0])];
    ans %= mod;
    ll rem = n - powers[0];
    //cout << "FIRST: " << ans << endl;
    //cout << pow2[(int) powers[0]] << endl;
    for(int i = 1; i < powers.size(); i++){
        ll prev = rem;
        rem -= powers[i];
        if(prev - rem < 2){
            continue;
        }
        ll delta = pow2[prev - 1] - pow2[rem] + mod;
        if(delta >= mod){
            delta -= mod;
        }
        ans += delta;
        if(ans >= mod){
            ans -= mod;
        }
    }
    cout << ans << endl;
    
    return 0;
}
