#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1957D

//this problem simplifies down to: count the number of ordered tuples (x, y, z), where f(x, z) ^ a[y] > f(x, z). 
//f(x, z) ^ a[y] > f(x, z) is only true if the most significant bit of a[y], denoted as s[y], is not present in
//f(x, z). 

//so, for each number, we want to find a fast way to count the number of subarrays such that 
//1. the subarray contains this number
//2. the subarray's xor sum does not contain this number's most significant bit. 

//first, for each bit, we can take a xor prefix sum. Since we want to count subarrays that contain our current
//number, lets say at index i, then our left ends have to be <= i, and right ends have to be >= i. Next, since we
//want to count subarrays that don't contain s[i], pfx[l] must equal pfx[r], at least for bit s[i]. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        n ++;
        vector<int> sbit(n);    //what is the most significant bit
        vector<vector<int>> bits(30, vector<int>(n, 0));
        for(int i = 1; i < n; i++){
            int a;
            cin >> a;
            for(int j = 0; j < 30; j++){
                if(a == 1){
                    sbit[i] = j;
                }
                bits[j][i] = a & 1;
                a /= 2;
            }
        }
        //compute pfx sums
        for(int i = 0; i < 30; i++){
            for(int j = 1; j < n; j++){
                bits[i][j] ^= bits[i][j - 1];
            }
        }
        //nr zeroes and nr ones sfx sums
        vector<vector<int>> z_sfx(30, vector<int>(n + 1, 0)), o_sfx(30, vector<int>(n + 1, 0));
        for(int i = 0; i < 30; i++){
            for(int j = n - 1; j >= 0; j--){
                z_sfx[i][j] = z_sfx[i][j + 1] + (bits[i][j] == 0);
                o_sfx[i][j] = o_sfx[i][j + 1] + (bits[i][j] == 1);
            }
        }
        ll ans = 0;
        for(int i = 1; i < n; i++){
            int s = sbit[i];
            ans += (ll) z_sfx[s][i] * (ll) (z_sfx[s][0] - z_sfx[s][i]);
            ans += (ll) o_sfx[s][i] * (ll) (o_sfx[s][0] - o_sfx[s][i]);
        }
        cout << ans << "\n";
    }
    
    return 0;
}
