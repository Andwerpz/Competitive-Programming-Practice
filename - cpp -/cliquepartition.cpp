#include <bits/stdc++.h>
typedef long long ll;
// typedef __int128 lll;
typedef long double ld;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1948E

//an upper bound on the maximum clique size is k. Because every node must differ in value by at least one, 
//and if a clique size is size k, the first indexed and last indexed node must have index difference k - 1, 
//the first and last element will have total difference k if they have adjacent values. 

//it just happens that I found a way to construct a clique of size k. So just use that strategy and partition the
//n nodes into the minimum amount of cliques. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        int maxc = k;
        int q = (n + maxc - 1) / maxc;
        vector<int> a(n), b(n);
        for(int i = 0; i < n; i += maxc) {
            int l = i;
            int r = min(n - 1, l + maxc - 1);
            int amt = r - l + 1;
            if(amt == 1){
                a[i] = i + 1;
                b[i] = (i / maxc) + 1;
                continue;
            }
            amt -= amt % 2;
            int l_val = amt / 2 + i;
            int r_val = amt / 2 + 1 + i;
            for(int j = l; j <= r; j++){
                b[j] = (i / maxc) + 1;
            }
            if(l <= r){
                a[l] = l_val;
                l ++;
                l_val += 2;
            }
            if(l <= r){
                a[r] = r_val;
                r --;
                r_val -= 2;
            }
            while(l <= r){
                a[l++] = l_val ++;
                if(l <= r){
                    a[r--] = r_val --;
                }
            }
        }
        for(int i = 0; i < n; i++){
            cout << a[i] << " \n"[i == n - 1];
        }
        cout << q << "\n";
        for(int i = 0; i < n; i++){
            cout << b[i] << " \n"[i == n - 1];
        }
    }
    
    return 0;
}
