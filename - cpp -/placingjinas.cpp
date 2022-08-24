#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1696E

//let's review the condition for a cell to be white: (x, y) is white if y < a_x. 
//this means that given an x coordinate, all cells with y coordinate less than a_x are white. 

//since a is non-increasing, this means that the white cells form a sort of right triangle with the right angle
//on (0, 0). 

//next, observe that the operation sequence doesn't affect the total amount of operations taken to 
//remove all the jinas. Say that n(x, y) is the total amount of dolls that will ever go through the cell (x, y). 
//n(x, y) also is equal to the amount of operations that we will have to perform on (x, y). Notice that
//n(x, y) = n(x - 1, y) + n(x, y - 1). Since the total amount of moves is simply equal to the sum of n(x, y) over all 
//white cells, the operation sequence can't affect it. 

//notice that the column x = 1 is simply the prefix sum for x = 0. This is actually true for all columns: col x is the
//prefix sum for col x - 1. This will be important later. 

//the arrangement of numbers created by n(x, y) is pascal's triangle. There is actually a formula to calculate any number
//in the triangle: n! / k! * (n - k)!, or n choose k, where n is the layer of the triangle and k is the index starting from the left. 

//since we know the fact that a given diagonal of the triangle is the prefix sum of the previous diagonal, we can just compute one value
//for each column, and sum them together to get the total amount of moves. 

ll mod = 1e9 + 7;

ll power(ll val, ll pow){
    if(pow == 0){
        return 1;
    }
    else if(pow == 1){
        return val;
    }
    ll half = power(val, pow / 2);
    return half * half % mod * (pow % 2 == 1? val : 1) % mod;
}

ll divide(ll a, ll b){  //a div b
    return a * power(b, mod - 2) % mod;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    //compute factorials
    vector<ll> f(1e6 + 1);
    f[0] = 1;
    f[1] = 1;
    for(int i = 2; i < f.size(); i++){
        f[i] = f[i - 1] * i % mod;
    }
    int n;
    cin >> n;
    ll ans = 0;
    for(int i = 0; i <= n; i++){
        ll next;
        cin >> next;
        if(next == 0){
            continue;
        }
        //r! / c! * (r - c)!
        ll r = i + next;
        ll c = i + 1;
        //cout << r << " " << c << endl;
        ans += divide(f[r], (f[c] * f[r - c]) % mod);
        ans %= mod;
    }
    cout << ans << "\n";
    
    return 0;
}
