#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1787E

//first, note that in order to break the array into k subarrays with xor sum equal to x, the xor sum of the entire subarray needs
//to be 0, if k is even, and x if k is odd. 

//if the above is true, then it is guaranteed that there are maximum k +- 2 * y partitions of the array where the partitions xor 
//to , where y is some 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        int n, k, x;
        cin >> n >> k >> x;
        //check if xor sum of array is equal to (k & 1) * x. 
        bool isValid = true;
        {
            int xsum = 0;
            for(int i = 1; i <= n; i++){
                xsum ^= i;
            }
            if(xsum != (k & 1) * x) {
                isValid = false;
            }
        }
        vector<vector<int>> a(0);
        vector<bool> v(n + 1, false);
        for(int i = 1; i <= n; i++){
            int xtgt = i ^ x;
            if(xtgt < 1 || xtgt > n || v[i] || v[xtgt]) {
                continue;
            }
            v[i] = true;
            v[xtgt] = true;
            a.push_back({i, xtgt});
        }
        vector<int> unv(0);
        for(int i = 1; i <= n; i++){
            if(!v[i]) {
                //cout << "UNV : " << i << "\n";
                unv.push_back(i);
            }
        }
        a.push_back(unv);
        if(a.size() < k) {
            isValid = false;
        }
        if(!isValid) {
            cout << "NO\n";
            continue;
        }
        cout << "YES\n";
        for(int j = a.size() - 1; j >= k; j--){
            for(int i = 0; i < a[j].size(); i++){
                a[0].push_back(a[j][i]);
            }
        }
        for(int i = 0; i < k; i++){
            cout << a[i].size() << " ";
            for(int j = 0; j < a[i].size(); j++){
                cout << a[i][j] << " ";
            }
            cout << "\n";
        }
    }
    
    return 0;
}
