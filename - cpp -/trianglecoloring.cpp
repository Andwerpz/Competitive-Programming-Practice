#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1795D

//first, determine how to construct the maximum sum. 

//note that a triangle with all three nodes of the same color is never optimal, as if you have a triangle
//with all three nodes having the same color, then there must be another triangle with all the same color, just
//the opposite color. You can just swap one color from each node, and you'll make the sum bigger. 

//so the optimal sum must happen when all triangles have two nodes of one color, and one node of the other color.

//now, we have to count how many ways there are to choose the colors. We'll call a triangle 'red' if it has majority red
//nodes, and 'blue' if otherwise. 

//note that the number of red triangles must equal the number of blue triangles, or else we won't have the same amount of
//red and blue nodes. Thus, the problem boils down to figuring out how many permutations there are of n / 6 red triangles
//and n / 6 blue triangles. We can use the n choose k formula to compute this. 

//after that, some triangles have several different ways of picking the color within itself. You must factor this in as well.

// - if all edges in the node are different, then the minimum edge will connect two nodes of the same value. 
// - if there are two same edges, and the third edge is greater, then there are two possible ways to choose the colors
// - if all edges are the same, then there are 3 ways to choose color; they are just rotations of each other.

ll mod = 998244353;

ll mul(ll a, ll b){
    return (a * b) % mod;
}

ll pow(ll a, ll b){
    if(b == 0){
        return 1;
    }
    ll ans = pow(a, b / 2);
    ans *= ans;
    ans %= mod;
    if(b % 2 == 1){
        ans *= a;
        ans %= mod;
    }
    return ans;
}

ll divide(ll a, ll b){
    return (a * pow(b, mod - 2)) % mod;
}

ll fac(ll a){
    ll ans = 1;
    for(ll i = 1; i <= a; i++){
        ans *= i;
        ans %= mod;
    }
    return ans;
}

ll nck(ll n, ll k){
    return divide(fac(n), mul(fac(n - k), fac(k)));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    ll ans = 1;
    for(int i = 0; i < n; i += 3){
        int a, b, c;
        cin >> a >> b >> c;
        if(a == b && b == c){
            ans *= 3;
            ans %= mod;
        }
        else if((a == b && c > a) || (b == c && a > c) || (c == a && b > a)){
            ans *= 2;
            ans %= mod;
        }
    }
    ans *= nck(n / 3, n / 6);
    ans %= mod;
    cout << ans << "\n";
    
    return 0;
}
