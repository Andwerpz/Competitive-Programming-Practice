#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//Codeforces - 1935B

//in order for us to split the array, and the mex to be the same, this mex value must not appear in the
//entire array. In other words, the segments mex must be the mex of the entire array. 

//once we find the mex, we can just split the array into two segments. If it isn't possible to split
//into two segments with equal mex, it's impossible to split into more than 2 segments. We can 
//do this split greedily; find the minimum prefix with the desired mex, then the entire rest of the
//array is the other segment. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        if(n == 1){
            cout << "-1\n";
            continue;
        }
        map<int, int> m;
        for(int i = 0; i < n; i++){
            m[a[i]] ++;
        }
        bool is_valid = true;
        int mex;
        for(int i = 0; i <= n; i++){
            if(!m.count(i)){
                mex = i;
                break;
            }
        }
        int l_mex = 0;
        int r_mex = 0;
        set<int> s;
        int ptr = -1;
        for(int i = 0; i < n; i++){
            s.insert(a[i]);
            while(s.count(l_mex)) {
                l_mex ++;
            }
            if(l_mex == mex) {
                ptr = i + 1;
                break;
            }
        }
        s.clear();
        for(int i = ptr; i < n; i++){
            s.insert(a[i]);
            while(s.count(r_mex)) {
                r_mex ++;
            }
        }
        if(l_mex != r_mex) {
            cout << "-1\n";
            continue;
        }
        cout << "2\n";
        cout << "1 " << ptr << "\n";
        cout << ptr + 1 << " " << n << "\n";
    }
    
    return 0;
}
