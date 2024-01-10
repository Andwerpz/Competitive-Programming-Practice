#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//https://codeforces.com/group/qcIqFPYhVr/contest/203881/problem/S

//first, we can keep track of the basis vectors of S. For this basis, we enforce that all
//basis vectors must have a unique largest bit. 

//next, to answer queries of type 2, we can construct the kth smallest number. First, 
//subtract 1 from k to make it 0 indexed. This is also to make the maximum number of bits
//in k equal to the number of basis vectors. 

//to construct, we can iterate i from b - 1 to 0, where b is the number of basis vectors. Let's
//also keep track of the number we're constructing, 'x', and initially assign it x := 0. 
//then, if the ith bit of k is on, we should get the ith most significant basis vector, 
//and make sure that the most significant bit in that basis vector is also on in x. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> basis(31, -1);
    int b = 0;
    while(n--){
        int t, k;
        cin >> t >> k;
        if(t == 1){
            //insert k into basis
            for(int i = 30; i >= 0; i--){
                if((k & 1 << i) == 0) {
                    continue;
                }
                if(basis[i] == -1){
                    b ++;
                    basis[i] = k;
                    break;
                }
                k ^= basis[i];
            }
        }
        else if(t == 2) {
            //find kth smallest number in vector space
            k --;
            int ans = 0;
            int bptr = 30;
            for(int i = b - 1; i >= 0; i--){
                while(basis[bptr] == -1){
                    bptr --;
                }
                if(((ans & 1 << bptr) == 0) != ((k & 1 << i) == 0)) {
                    ans ^= basis[bptr];
                }
                bptr --;
            }
            cout << ans << "\n";
        }
    }
    
    return 0;
}
