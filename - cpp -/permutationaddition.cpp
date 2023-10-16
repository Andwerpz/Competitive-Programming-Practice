#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//AtCoder - ARC159C

//the actual solution is to notice that you can do +1 / -1 on any pair of elements by doing two 
//permutation additions. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i].first;
        a[i].second = i;
    }
    vector<vector<int>> perm(0);
    while(perm.size() <= 1e4) {
        sort(a.begin(), a.end());
        bool equal = true;
        bool twoval = true;
        int mxdiff = 0;
        for(int i = 1; i < n; i++){
            mxdiff = max(mxdiff, a[i].first - a[i - 1].first);
            if(a[i].first != a[i - 1].first){
                if(equal) {
                    equal = false;
                }
                else {
                    twoval = false;
                }
                break;
            }
        }
        if(equal) {
            break;
        }
        if(twoval && (mxdiff == 1 || mxdiff == 2)){

        }
        vector<int> nperm(n, 0);
        for(int i = 0; i < n; i++){
            a[i].first += n - i;
            nperm[a[i].second] = n - i;
        }
        perm.push_back(nperm);
    }
    if(perm.size() > 1e4) {
        cout << "No\n";
        return 0;
    }
    cout << "Yes\n";
    cout << perm.size() << "\n";
    for(int i = 0; i < perm.size(); i++){
        for(int j = 0; j < n; j++){
            cout << perm[i][j] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
