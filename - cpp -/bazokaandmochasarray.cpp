#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1975A

//each operation just rotates the array some amount. So any array that can be sorted should be a rotation of an already
//sorted array. 

//since n is small, it's sufficient to just try all possible rotations. 

bool is_sorted(vector<int>& a){
    for(int i = 1; i < a.size(); i++){
        if(a[i] < a[i - 1]){
            return false;
        }
    }
    return true;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        bool is_valid = is_sorted(a);
        for(int i = 0; i < n; i++){
            int tmp = a[0];
            a.erase(a.begin());
            a.push_back(tmp);
            is_valid |= is_sorted(a);
        }
        cout << (is_valid? "Yes" : "No") << "\n";
    }
    
    return 0;
}